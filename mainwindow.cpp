#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);
    ui->textBrowser->setStyleSheet("font: 24px; font-weight: bold; color: #00cccc; background-color: #001a1a;");
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    QString rgbText;

    cv::VideoCapture testCam;
    if(!testCam.open(0))
    {
        /*QMessageBox::critical(this,
                              "Camera Error",
                              "Camera not found!");*/
        rgbText = "Camera not found!\nPlease Select a Video File.";
        ui->textBrowser->setText(rgbText);
        testCam.release();
        return;
    }
    else
    {

        testCam.release();
        cpThread = new CaptureThread{ this, "0"};
        QObject::connect(cpThread, &CaptureThread::frameCaptured, this, &MainWindow::processFrame);
        QObject::connect(cpThread, &CaptureThread::frameCurrent, this, &MainWindow::setCurrentFrame);
        QObject::connect(cpThread, &CaptureThread::frameTotal, this, &MainWindow::setTotalFrame);
        connect(cpThread, &CaptureThread::finished, cpThread, &QObject::deleteLater);
        connect(cpThread, &CaptureThread::finished, [&](){ cpThread = nullptr; });

        cpThread->start();

        ui->startBtn->setText("Stop");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBtn_pressed()
{
    if(ui->startBtn->text() == "Start")
    {
        auto videoFile = ui->videoEdit->text().trimmed().toStdString();
        if(videoFile.empty())
        {
            QMessageBox::warning(this,
                                 "Warning",
                                 "Please select open a video file or enter camera index number !");
            return;
        }

        cv::VideoCapture testFile;
        if(!testFile.open(ui->videoEdit->text().trimmed().toStdString()))
        {
            QMessageBox::critical(this,
                                  "Video Error",
                                  "Make sure you entered a correct and supported video file path,"
                                  "<br>or a correct RTSP feed URL or correct camera index!");
            testFile.release();
            return;
        }

        testFile.release();

        /*hue_filter = new KalmanFilter(KF_VAR_ACCEL);
        hue_filter->Reset(0);*/

        p_start = QDateTime::currentDateTime();

        cpThread = new CaptureThread{ this, videoFile};
        QObject::connect(cpThread, &CaptureThread::frameCaptured, this, &MainWindow::processFrame);
        QObject::connect(cpThread, &CaptureThread::frameCurrent, this, &MainWindow::setCurrentFrame);
        QObject::connect(cpThread, &CaptureThread::frameTotal, this, &MainWindow::setTotalFrame);
        connect(cpThread, &CaptureThread::finished, cpThread, &QObject::deleteLater);
        connect(cpThread, &CaptureThread::finished, [&](){ cpThread = nullptr; });

        cpThread->start();

        ui->startBtn->setText("Stop");
    }
    else
    {
        if(cpThread)
        {
            cpThread->abort();
            cpThread->wait();
        }

        if(hue_filter)
            delete hue_filter;

        ui->startBtn->setText("Start");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(cpThread)
    {
        qDebug() << "Removing thread";
        cpThread->abort();
        cpThread->wait();
    }
    event->accept();
}


void MainWindow::on_openBtn_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,  tr("Choose Video File"), QDir::currentPath() , QLatin1String("*.mp4"));
    if (!fileName.isEmpty())
    {
        ui->videoEdit->setText(fileName);
        on_startBtn_pressed();
    }
}

void MainWindow::processFrame(cv::Mat &frame)
{
    p_end = QDateTime::currentDateTime();
    p_dt = p_start.msecsTo(p_end) / 1000.;

    cv::Mat matProcessed;
    matOriginal = frame;

    if(!frame.empty() && p_dt > 0)
    {      
        int len = frame.total() * frame.elemSize();

        QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
        pixmap.setPixmap( QPixmap::fromImage(qimgOriginal.rgbSwapped()) );

        cv::Vec3b pixel = matOriginal.at<cv::Vec3b>(cv::Point (qimgOriginal.height() / 2, qimgOriginal.width() / 2));
        int b, g, r;
        b = pixel[0];
        g = pixel[1];
        r = pixel[2];

        RGB data = RGB(r, g, b);
        HSV value = RGBToHSV(data);       

        /*hue_filter->Update(value.H, KF_VAR_MEASUREMENT, p_dt);
        auto filteredHue = static_cast<double>(hue_filter->GetXAbs());  */

        QVector<float> glucose{};
        glucose.insert(0,0);
        glucose.insert(1,0);
        calcGlucose(value.H, glucose);
        glucose.insert(1, static_cast<float>(floor(glucose[1]*100) / 100));

        QString rgbText = "HSV: "   + QString::number(value.H, 'f', 0) + " - "
                                      + QString::number(value.S, 'f', 0) + " - "
                                      + QString::number(value.V, 'f', 0)
                        + "\nR: " + QString::number(r, 'f', 0)
                        + "\nG: " + QString::number(g, 'f', 0)
                        + "\nB: " + QString::number(b, 'f', 0)
                        + "\nRemaining: " + QString::number(totalFrame - currentFrame) + " / " + QString::number(totalFrame)
                        + "\nGlucose: " + QString::number(static_cast<double>(glucose.at(1)), 'f', 1) + " mg/dL";

        ui->textBrowser->setText(rgbText);
        ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

        if(currentFrame == totalFrame)
             ui->startBtn->setText("Start");
    }

    p_start = p_end;

}

float MainWindow::calcGradient(float h1, float h2, float g1, float g2, float hue)
{
    float steps = 100;
    //h1=h1/360;
    //h2=h2/360;
    //hue=hue/360;
    float d = h2 - h1;
    float g = g2 - g1;
    float ginc = g / steps;
    float p = 0, p2 = 0;
    float hi = 0, hi2 = 0;
    float gret = g1;
    float diff1 = 0, diff2 = 0;
    for (int i = 0;i < steps;i++)
    {
        p = i / steps;
        p2 = (i + 1) / steps;
        hi = h1 + (d*p);
        hi2 = h1 + (d*p2);
        /*if(hi<0)
                        hi=hi+1;
                    else if(hi>1)
                        hi=hi-1;
                    if(hi2<0)
                        hi2=hi2+1;
                    else if(hi2>1)
                        hi2=hi2-1;*/
        diff1 = abs(hue - hi);
        diff2 = abs(hue - hi2);
        //diff=Math.abs(hi-hi2);
        if (hue > hi && hue > hi2)
        {
            gret = gret + ginc;
            continue;
        }
        else if (diff2 > diff1)
        {
            return gret;
        }
        else if (diff1 >= diff2)
        {
            gret = gret + ginc;
            return gret;
        }
        //gret=gret+ginc;
    }
    return 0;
}
void MainWindow::calcGlucose(float h, QVector<float> &g_vector)
{
    if (h >= 50 && h <= 60)
    {
        g_vector.insert(0, 0);
    }
    else if (h > 60 && h <= 66)
    {
        g_vector.insert(0, 30);
        g_vector.insert(1,calcGradient(60,66,0,30,h));
    }
    else if (h > 66 && h <= 70)
    {
        g_vector.insert(0, 80);
        g_vector.insert(1,calcGradient(66,70,30,80,h));
    }
    else if (h > 70 && h < 79)
    {
        g_vector.insert(0,120);
        g_vector.insert(1,calcGradient(70,79,80,120,h));
    }
    else if (h >= 79 && h <= 83)
    {
        g_vector.insert(0, 160);
        g_vector.insert(1,calcGradient(79,83,120,160,h));
    }
    else if (h > 83 && h < 88)
    {
        g_vector.insert(0, 230);
        g_vector.insert(1,calcGradient(83,88,160,230,h));
    }
    else if (h >= 88 && h <= 93)
    {
        g_vector.insert(0, 300);
        g_vector.insert(1,calcGradient(88,93,230,300,h));
    }
    else if (h > 93 && h < 152)
    {
        g_vector.insert(0, 375);
        g_vector.insert(1,calcGradient(93,152,300,375,h));
    }
    else if (h >= 152 && h <= 156)
    {
        g_vector.insert(0, 450);
        g_vector.insert(1,calcGradient(152,156,375,450,h));
    }
    else if (h >= 157 && h <= 180)
    {
       g_vector.insert(0, 500);
       g_vector.insert(1, 0);
    }

}

QString MainWindow::GetMatDepth(const cv::Mat& mat)
{
    const int depth = mat.depth();

    switch (depth)
    {
    case CV_8U:  return "CV_8U";
    case CV_8S:  return "CV_8S";
    case CV_16U: return "CV_16U";
    case CV_16S: return "CV_16S";
    case CV_32S: return "CV_32S";
    case CV_32F: return "CV_32F";
    case CV_64F: return "CV_64F";
    default:
        return "Invalid depth type of matrix!";
    }
}

QString MainWindow::GetMatType(const cv::Mat& mat)
{
    const int mtype = mat.type();

    switch (mtype)
    {
    case CV_8UC1:  return "CV_8UC1";
    case CV_8UC2:  return "CV_8UC2";
    case CV_8UC3:  return "CV_8UC3";
    case CV_8UC4:  return "CV_8UC4";

    case CV_8SC1:  return "CV_8SC1";
    case CV_8SC2:  return "CV_8SC2";
    case CV_8SC3:  return "CV_8SC3";
    case CV_8SC4:  return "CV_8SC4";

    case CV_16UC1: return "CV_16UC1";
    case CV_16UC2: return "CV_16UC2";
    case CV_16UC3: return "CV_16UC3";
    case CV_16UC4: return "CV_16UC4";

    case CV_16SC1: return "CV_16SC1";
    case CV_16SC2: return "CV_16SC2";
    case CV_16SC3: return "CV_16SC3";
    case CV_16SC4: return "CV_16SC4";

    case CV_32SC1: return "CV_32SC1";
    case CV_32SC2: return "CV_32SC2";
    case CV_32SC3: return "CV_32SC3";
    case CV_32SC4: return "CV_32SC4";

    case CV_32FC1: return "CV_32FC1";
    case CV_32FC2: return "CV_32FC2";
    case CV_32FC3: return "CV_32FC3";
    case CV_32FC4: return "CV_32FC4";

    case CV_64FC1: return "CV_64FC1";
    case CV_64FC2: return "CV_64FC2";
    case CV_64FC3: return "CV_64FC3";
    case CV_64FC4: return "CV_64FC4";

    default:
        return "Invalid type of matrix!";
    }
}

void MainWindow::setTotalFrame(int value)
{
    totalFrame = value;
}

void MainWindow::setCurrentFrame(int value)
{
    currentFrame = value;
}



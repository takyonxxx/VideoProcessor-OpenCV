#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include "capturethread.h"
#include "functions.h"
#include "kalmanfilter.h"

namespace Ui {
class MainWindow;
}

class KalmanFilter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_startBtn_pressed();
    void on_openBtn_clicked();
    void processFrame(cv::Mat&);
    void setCurrentFrame(int value);
    void setTotalFrame(int value);

private:
    float calcGradient(float h1, float h2, float g1, float g2, float hue);
    void calcGlucose(float h, QVector<float> &g_vector);

    QString GetMatDepth(const cv::Mat& mat);
    QString GetMatType(const cv::Mat& mat);

    Ui::MainWindow *ui;
    QGraphicsPixmapItem pixmap;

    cv::Mat matOriginal;
    QTimer* tmrTimer;

    CaptureThread* cpThread;
    KalmanFilter *red_filter;
    KalmanFilter *hue_filter;

    qreal p_dt;
    QDateTime p_start;
    QDateTime p_end;

    int currentFrame;
    int totalFrame;

};

#endif // MAINWINDOW_H

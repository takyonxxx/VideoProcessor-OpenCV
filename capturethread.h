#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QMutexLocker>
#include <QTimer>


class CaptureThread : public QThread
{
    Q_OBJECT

public:

    explicit CaptureThread(QObject *parent, std::string videoFile);

    void abort();

protected:

    void run();

signals:
    void frameCaptured(cv::Mat);
    void frameCurrent(int);
    void frameTotal(int);

public slots:
    void captureFrame();

private:

    QMutex mutex;
    cv::VideoCapture videoCapturer;
    cv::Mat capturedFrame;
    std::string videoFile;
    bool m_abort {false};
};


#endif // CAPTURETHREAD_H

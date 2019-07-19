#include "capturethread.h"
Q_DECLARE_METATYPE(cv::Mat);
using namespace std;

CaptureThread::CaptureThread(QObject* parent, std::string videoFile)
    :QThread(parent)
{
    qRegisterMetaType<cv::Mat>();
    this->videoFile = videoFile;

    if(!videoCapturer.open(videoFile))
    {
        cout << "Make sure you entered a correct and supported video file path" << endl;
        return;
    }

    if(!videoCapturer.set(cv::CAP_PROP_FORMAT, 16U))
    {
        cout << "Try setting the property cv::CAP_PROP_FORMAT to cv::16U not success!"  << endl;
        return;
    }
}

void CaptureThread::abort()
{
    m_abort = true;
}

void CaptureThread::run()
{    
    const auto rate = videoCapturer.get(cv::CAP_PROP_FPS);
    const auto delay = static_cast<int>(round(1000 / rate));

    while(!m_abort)
    {
        captureFrame();
        QThread::msleep(delay);
    }
}

void CaptureThread::captureFrame()
{
    //QMutexLocker locker(&mutex);

    if(videoCapturer.isOpened()){
        videoCapturer.read(capturedFrame);

        /*std::cout << videoCapturer.get(cv::CAP_PROP_FPS) << std::endl;
        std::cout << videoCapturer.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
        std::cout << videoCapturer.get(cv::CAP_PROP_POS_AVI_RATIO) << std::endl;
        std::cout << videoCapturer.get(cv::CAP_PROP_POS_FRAMES) << std::endl;
        std::cout << videoCapturer.get(cv::CAP_PROP_POS_MSEC) << std::endl;
        std::cout << "------------------------------------------" << std::endl;*/
        auto totalFrame = static_cast<int>(videoCapturer.get(cv::CAP_PROP_FRAME_COUNT));
        auto currentFrame = static_cast<int>(videoCapturer.get(cv::CAP_PROP_POS_FRAMES));

        emit frameCurrent(currentFrame);
        emit frameTotal(totalFrame);
        emit frameCaptured(capturedFrame);
    }
}


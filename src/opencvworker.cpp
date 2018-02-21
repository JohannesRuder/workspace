//
// Created by hannes on 18.02.18.
//

#include "opencvworker.h"

OpenCvWorker::OpenCvWorker(QObject* parent)
    : QObject{parent}, status_{false}, toggle_stream_{false}, update_frame_{false}
{
    capture = new cv::VideoCapture();
}

OpenCvWorker::~OpenCvWorker()
{
    if (capture->isOpened())
        capture->release();
    delete capture;
}

void OpenCvWorker::CheckIfDeviceAlreadyOpened(QString filename)
{
    if (capture->isOpened())
        capture->release();
    capture->open(filename.toStdString());

    QTime temp(0, 0, 0);
    const int s_to_ms = 1000;
    auto ms_per_frame = static_cast<int>(1 / capture->get(cv::CAP_PROP_FPS) * s_to_ms);
    QTime videoEndTime = temp.addMSecs(static_cast<int>(capture->get(cv::CAP_PROP_FRAME_COUNT) * ms_per_frame));
    emit SendVideoEndTime(videoEndTime);

    emit SendVideoFrameCount(static_cast<int>(capture->get(cv::CAP_PROP_FRAME_COUNT)));
}

void OpenCvWorker::ReceiveGrabFrame()
{
    if (!toggle_stream_ && !update_frame_)
        return;

    (*capture) >> original_frame_;
    if (original_frame_.empty())
        return;

    QTime temp(0, 0, 0);
    QTime video_current_time = temp.addMSecs(static_cast<int>(capture->get(cv::CAP_PROP_POS_MSEC)));

    emit SendFrame(ASM::cvMatToQImage(original_frame_));
    emit SendVideoCurrentTime(video_current_time);

    emit SendVideoCurrentFrameNumber(static_cast<int>(capture->get(cv::CAP_PROP_POS_FRAMES)));

    update_frame_ = false;
}

void OpenCvWorker::ReceiveOpenVideoFile(const QString& video_filename)
{
    CheckIfDeviceAlreadyOpened(video_filename);
    if (!capture->isOpened())
    {
        status_ = false;
        return;
    }

    status_ = true;
}

void OpenCvWorker::ReceiveToggleStream()
{
    toggle_stream_ = !toggle_stream_;
}

void OpenCvWorker::ReceiveUpdateFrame()
{
    update_frame_ = true;
}

void OpenCvWorker::ReceiveGoTo(int video_frame_number)
{
    capture->set(cv::CAP_PROP_POS_FRAMES, video_frame_number);
}

void OpenCvWorker::ReceiveGoToStart()
{
    capture->set(cv::CAP_PROP_POS_FRAMES, 0);
}

void OpenCvWorker::ReceiveNext()
{
    if (capture->get(cv::CAP_PROP_POS_FRAMES) + 5 * capture->get(cv::CAP_PROP_FPS) <=
        capture->get(cv::CAP_PROP_FRAME_COUNT))
    {
        capture->set(cv::CAP_PROP_POS_FRAMES,
                     capture->get(cv::CAP_PROP_POS_FRAMES) + 5 * capture->get(cv::CAP_PROP_FPS));
    }
    else
    {
        capture->set(cv::CAP_PROP_POS_FRAMES, capture->get(cv::CAP_PROP_FRAME_COUNT));
    }
}

void OpenCvWorker::ReceivePrevious()
{
    if (capture->get(cv::CAP_PROP_POS_FRAMES) - 5 * capture->get(cv::CAP_PROP_FPS) >= 0)
    {
        capture->set(cv::CAP_PROP_POS_FRAMES,
                     capture->get(cv::CAP_PROP_POS_FRAMES) - 5 * capture->get(cv::CAP_PROP_FPS));
    }
    else
    {
        capture->set(cv::CAP_PROP_POS_FRAMES, 0);
    }
}

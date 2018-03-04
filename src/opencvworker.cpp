//
// Created by hannes on 18.02.18.
//

#include "opencvworker.h"

OpenCvWorker::OpenCvWorker(QObject* parent)
    : QObject{parent}, status_{false}, toggle_stream_{false}, update_frame_{false}
{
    capture_ = new cv::VideoCapture();
}

OpenCvWorker::~OpenCvWorker()
{
    if (capture_->isOpened())
        capture_->release();
    delete capture_;
}

void OpenCvWorker::CheckIfDeviceAlreadyOpened(QString filename)
{
    if (capture_->isOpened())
        capture_->release();
    capture_->open(filename.toStdString());

    QTime temp(0, 0, 0);
    const int s_to_ms = 1000;
    auto ms_per_frame = static_cast<int>(1 / capture_->get(cv::CAP_PROP_FPS) * s_to_ms);
    auto videoEndTime = temp.addMSecs(static_cast<int>(capture_->get(cv::CAP_PROP_FRAME_COUNT) * ms_per_frame));
    emit SendVideoEndTime(videoEndTime);

    emit SendVideoFrameCount(static_cast<int>(capture_->get(cv::CAP_PROP_FRAME_COUNT)));
}

void OpenCvWorker::ReceiveGrabFrame()
{
    if (!toggle_stream_ && !update_frame_)
        return;

    (*capture_) >> original_frame_;
    if (original_frame_.empty())
        return;

    QTime temp(0, 0, 0);
    auto video_current_time = temp.addMSecs(static_cast<int>(capture_->get(cv::CAP_PROP_POS_MSEC)));

    emit SendFrame(ASM::cvMatToQImage(original_frame_));
    emit SendVideoCurrentTime(video_current_time);

    emit SendVideoCurrentFrameNumber(static_cast<int>(capture_->get(cv::CAP_PROP_POS_FRAMES)));

    update_frame_ = false;
}

void OpenCvWorker::ReceiveOpenVideoFile(const QString& video_filename)
{
    CheckIfDeviceAlreadyOpened(video_filename);
    if (!capture_->isOpened())
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
    capture_->set(cv::CAP_PROP_POS_FRAMES, video_frame_number);
}

void OpenCvWorker::ReceiveGoToStart()
{
    capture_->set(cv::CAP_PROP_POS_FRAMES, 0);
}

void OpenCvWorker::ReceiveNext()
{
    if (capture_->get(cv::CAP_PROP_POS_FRAMES) + 5 * capture_->get(cv::CAP_PROP_FPS) <=
        capture_->get(cv::CAP_PROP_FRAME_COUNT))
    {
        capture_->set(cv::CAP_PROP_POS_FRAMES,
                     capture_->get(cv::CAP_PROP_POS_FRAMES) + 5 * capture_->get(cv::CAP_PROP_FPS));
    }
    else
    {
        capture_->set(cv::CAP_PROP_POS_FRAMES, capture_->get(cv::CAP_PROP_FRAME_COUNT));
    }
}

void OpenCvWorker::ReceivePrevious()
{
    if (capture_->get(cv::CAP_PROP_POS_FRAMES) - 5 * capture_->get(cv::CAP_PROP_FPS) >= 0)
    {
        capture_->set(cv::CAP_PROP_POS_FRAMES,
                     capture_->get(cv::CAP_PROP_POS_FRAMES) - 5 * capture_->get(cv::CAP_PROP_FPS));
    }
    else
    {
        capture_->set(cv::CAP_PROP_POS_FRAMES, 0);
    }
}

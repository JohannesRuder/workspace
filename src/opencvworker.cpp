//
// Created by hannes on 18.02.18.
//

#include "opencvworker.h"

OpenCvWorker::OpenCvWorker(QObject* parent) : QObject{parent}, status{false}, toggleStream{false}, updateFrame{false}
{
    cap = new cv::VideoCapture();
}

OpenCvWorker::~OpenCvWorker()
{
    if (cap->isOpened())
        cap->release();
    delete cap;
}

void OpenCvWorker::checkIfDeviceAlreadyOpened(QString filename)
{
    if (cap->isOpened())
        cap->release();
    cap->open(filename.toStdString());

    QTime temp(0, 0, 0);
    QTime videoEndTime = temp.addMSecs(cap->get(cv::CAP_PROP_FRAME_COUNT) * 1 / cap->get(cv::CAP_PROP_FPS) * 1000);
    //    emit sendVideoEndTime( videoEndTime );

    //    emit sendVideoFrameCount( cap->get( cv::CAP_PROP_FRAME_COUNT ) );
}

void OpenCvWorker::receiveGrabFrame()
{
    if (!toggleStream && !updateFrame)
        return;

    (*cap) >> _frameOriginal;
    if (_frameOriginal.empty())
        return;

    QTime temp(0, 0, 0);
    QTime videoCurrentTime = temp.addMSecs(cap->get(cv::CAP_PROP_POS_MSEC));

    //    emit sendFrame(ASM::cvMatToQImage(_frameOriginal));
    //    emit sendVideoCurrentTime( videoCurrentTime );

    //    emit sendVideoCurrentFrameNumber( cap->get( cv::CAP_PROP_POS_FRAMES ) );

    updateFrame = false;
}

void OpenCvWorker::receiveOpenVideoFile(QString videoFileName)
{
    checkIfDeviceAlreadyOpened(videoFileName);
    if (!cap->isOpened())
    {
        status = false;
        return;
    }

    status = true;
}

void OpenCvWorker::receiveToggleStream()
{
    toggleStream = !toggleStream;
}

void OpenCvWorker::receiveUpdateFrame()
{
    updateFrame = true;
}

void OpenCvWorker::receiveGoTo(int videoFrameNumber)
{
    cap->set(cv::CAP_PROP_POS_FRAMES, videoFrameNumber);
}

void OpenCvWorker::receiveGoToStart()
{
    cap->set(cv::CAP_PROP_POS_FRAMES, 0);
}

void OpenCvWorker::receiveNext()
{
    if (cap->get(cv::CAP_PROP_POS_FRAMES) + 5 * cap->get(cv::CAP_PROP_FPS) <= cap->get(cv::CAP_PROP_FRAME_COUNT))
    {
        cap->set(cv::CAP_PROP_POS_FRAMES, cap->get(cv::CAP_PROP_POS_FRAMES) + 5 * cap->get(cv::CAP_PROP_FPS));
    }
    else
    {
        cap->set(cv::CAP_PROP_POS_FRAMES, cap->get(cv::CAP_PROP_FRAME_COUNT));
    }
}

void OpenCvWorker::receivePrevious()
{
    if (cap->get(cv::CAP_PROP_POS_FRAMES) - 5 * cap->get(cv::CAP_PROP_FPS) >= 0)
    {
        cap->set(cv::CAP_PROP_POS_FRAMES, cap->get(cv::CAP_PROP_POS_FRAMES) - 5 * cap->get(cv::CAP_PROP_FPS));
    }
    else
    {
        cap->set(cv::CAP_PROP_POS_FRAMES, 0);
    }
}

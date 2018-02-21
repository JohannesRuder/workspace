//
// Created by hannes on 18.02.18.
//

#ifndef WORKSPACE_OPENCVWORKER_H
#define WORKSPACE_OPENCVWORKER_H

#include <QImage>
#include <QObject>
#include <QTime>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "convopencv2qt.h"

class OpenCvWorker : public QObject
{
    Q_OBJECT

  private:
    cv::Mat original_frame_;
    cv::Mat processed_frame_;
    cv::VideoCapture* capture;

    bool status_;
    bool toggle_stream_;
    bool update_frame_;

    void CheckIfDeviceAlreadyOpened(QString filename);

  public:
    explicit OpenCvWorker(QObject* parent = 0);
    ~OpenCvWorker();

  signals:
    void SendFrame(QImage processed_frame);
    void SendVideoEndTime(QTime video_end_time);
    void SendVideoFrameCount(int video_frame_count);
    void SendVideoCurrentTime(QTime video_current_time);
    void SendVideoCurrentFrameNumber(int video_current_frame_number);

  public slots:
    void ReceiveGrabFrame();
    void ReceiveOpenVideoFile(const QString& video_filename);
    void ReceiveToggleStream();
    void ReceiveUpdateFrame();
    void ReceiveGoTo(int video_frame_number);
    void ReceiveGoToStart();
    void ReceiveNext();
    void ReceivePrevious();
};

#endif  // WORKSPACE_OPENCVWORKER_H

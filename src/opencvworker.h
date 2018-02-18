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
    cv::Mat _frameOriginal;
    cv::Mat _frameProcessed;
    cv::VideoCapture* cap;

    bool status;
    bool toggleStream;
    bool updateFrame;

    void checkIfDeviceAlreadyOpened(QString filename);

  public:
    explicit OpenCvWorker(QObject* parent = 0);
    ~OpenCvWorker();

  signals:
    //    void sendFrame( QImage frameProcessed );
    //    void sendVideoEndTime( QTime videoEndTime );
    //    void sendVideoFrameCount( int videoFrameCount );
    //    void sendVideoCurrentTime( QTime videoCurrentTime );
    //    void sendVideoCurrentFrameNumber( int videoCurrentFrameNumber );

  public slots:
    void receiveGrabFrame();
    void receiveOpenVideoFile(QString videoFileName);
    void receiveToggleStream();
    void receiveUpdateFrame();
    void receiveGoTo(int videoFrameNumber);
    void receiveGoToStart();
    void receiveNext();
    void receivePrevious();
};

#endif  // WORKSPACE_OPENCVWORKER_H

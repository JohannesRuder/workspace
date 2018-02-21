//
// Created by hannes on 18.02.18.
//

#ifndef WORKSPACE_MAINWINDOW_H
#define WORKSPACE_MAINWINDOW_H

#include "game.h"
#include "season.h"
#include "opencvworker.h"

#include <opencv2/core/core.hpp>

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QDebug>

namespace Ui {
    class MainWindow;
}

namespace {
    Season season;
    Game game;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui_;
    QThread *thread_;
    QTimer *worker_trigger_;

    void Setup();

signals:
    void SendOpenVideoFile(QString filename);
    void SendToggleStream();
    void SendUpdateFrame();
    void SendGoTo(int video_frame_number);
    void SendGoToStart();
    void SendNext();
    void SendPrevious();
    void SendGrabFrame();
    void SendVideoFrameInterval(int inteval_in_ms);

private slots:
    void ReceiveFrame(QImage frame);
    void ReceiveVideoEndTime(QTime video_end_time);
    void ReceiveVideoFrameCount(int video_frame_count);
    void ReceiveVideoCurrentTime(QTime video_current_time);
    void ReceiveVideoCurrentFrameNumber(int video_current_frame_number);
    void ReceiveToggleStream();
    void ReceiveGoToStart();
    void ReceiveNext();
    void ReceivePrevious();
    void on_horizontalSliderVideoSpeed_valueChanged(int value);
    void on_horizontalSliderVideoPosition_sliderPressed();
    void on_horizontalSliderVideoPosition_sliderReleased();
    void on_actionOpenGame_triggered();
    void on_actionNewSeason_triggered();
    void on_actionSave_triggered();
    void on_actionOpenSeason_triggered();
    void on_actionSaisonAnsicht_triggered();
    void on_actionSpielAnsicht_triggered();
    void on_pushButtonOpenSeasonFile_clicked();
    void on_pushButtonNewGame_clicked();
    void on_tableWidgetGames_doubleClicked(const QModelIndex &index);
    void on_lineEditSeasonName_textChanged(const QString &arg1);
};

#endif //WORKSPACE_MAINWINDOW_H

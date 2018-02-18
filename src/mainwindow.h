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
    Ui::MainWindow *ui;
    QThread *thread;
    QTimer *workerTrigger;

    void setup();

signals:
    void sendOpenVideoFile( QString filename );
    void sendToggleStream();
    void sendUpdateFrame();
    void sendGoTo( int videoFrameNumber );
    void sendGoToStart();
    void sendNext();
    void sendPrevious();
    void sendGrabFrame();
    void sendVideoFrameInterval( int intevalMSec );

private slots:
    void receiveFrame( QImage frame );
    void receiveVideoEndTime( QTime videoEndTime );
    void receiveVideoFrameCount( int videoFrameCount );
    void receiveVideoCurrentTime( QTime videoCurrentTime );
    void receiveVideoCurrentFrameNumber( int videoCurrentFrameNumber );
    void receiveToggleStream();
    void receiveGoToStart();
    void receiveNext();
    void receivePrevious();
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

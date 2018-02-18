//
// Created by hannes on 18.02.18.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
    ui->stackedWidget_2->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    thread->quit();
    while(!thread->isFinished());

    delete thread;
    delete ui;
}

void MainWindow::setup()
{
    thread = new QThread();
    auto *worker = new OpenCvWorker();
    workerTrigger = new QTimer();
    workerTrigger->setInterval( 1000/60 );

    connect( workerTrigger, SIGNAL( timeout() ), worker, SLOT( receiveGrabFrame() ) );
    connect( thread, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect( thread, SIGNAL( finished() ), workerTrigger, SLOT( deleteLater() ) );
    connect( this, SIGNAL( sendOpenVideoFile( QString ) ), worker, SLOT( receiveOpenVideoFile( QString ) ) );
    connect( this, SIGNAL( sendToggleStream() ), worker, SLOT( receiveToggleStream() ) );
    connect( ui->pushButtonPlay, SIGNAL( clicked(bool) ), this, SLOT( receiveToggleStream() ) );
    connect( ui->pushButtonGoToStart, SIGNAL( clicked(bool) ), this, SLOT( receiveGoToStart() ) );
    connect( this, SIGNAL( sendGoToStart() ), worker, SLOT( receiveGoToStart() ) );
    connect( this, SIGNAL( sendUpdateFrame() ), worker, SLOT( receiveUpdateFrame() ) );
    connect( this, SIGNAL( sendGrabFrame() ), worker, SLOT( receiveGrabFrame() ) );
    connect( ui->pushButtonNext, SIGNAL( clicked(bool) ), this, SLOT( receiveNext() ) );
    connect( this, SIGNAL( sendNext() ), worker, SLOT( receiveNext() ) );
    connect( ui->pushButtonPrevious, SIGNAL( clicked(bool) ), this, SLOT( receivePrevious() ) );
    connect( this, SIGNAL( sendPrevious() ), worker, SLOT( receivePrevious() ) );
    connect( worker, SIGNAL( sendFrame(QImage) ), this, SLOT( receiveFrame(QImage) ) );
    connect( thread, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect( thread, SIGNAL( finished() ), workerTrigger, SLOT( deleteLater() ) );
    connect( worker, SIGNAL( sendVideoEndTime(QTime) ), this, SLOT( receiveVideoEndTime(QTime) ) );
    connect( worker, SIGNAL( sendVideoFrameCount(int) ), this, SLOT( receiveVideoFrameCount(int) ) );
    connect( worker, SIGNAL( sendVideoCurrentTime(QTime) ), this, SLOT( receiveVideoCurrentTime(QTime) ) );
    connect( worker, SIGNAL( sendVideoCurrentFrameNumber(int) ), this, SLOT( receiveVideoCurrentFrameNumber(int) ) );
    connect( this, SIGNAL( sendGoTo(int) ), worker, SLOT( receiveGoTo(int) ) );
    connect( this, SIGNAL( sendVideoFrameInterval(int) ), workerTrigger, SLOT( start(int) ) );

    workerTrigger->start();
    worker->moveToThread(thread);
    workerTrigger->moveToThread(thread);

    thread->start();
}

void MainWindow::receiveFrame(QImage frame)
{
    ui->labelViewVideo->setPixmap(QPixmap::fromImage(frame));
}

void MainWindow::receiveVideoEndTime(QTime videoEndTime)
{
    ui->labelVideoLength->setText( videoEndTime.toString("H:mm:ss") );
}

void MainWindow::receiveVideoFrameCount(int videoFrameCount)
{
    ui->horizontalSliderVideoPosition->setMaximum( videoFrameCount );
}

void MainWindow::receiveVideoCurrentTime(QTime videoCurrentTime)
{
    ui->labelVideoPosition->setText( videoCurrentTime.toString("H:mm:ss") );
}

void MainWindow::receiveVideoCurrentFrameNumber( int videoCurrentFrameNumber )
{
    ui->horizontalSliderVideoPosition->setValue( videoCurrentFrameNumber );
}

void MainWindow::receiveToggleStream()
{
    if(!ui->pushButtonPlay->text().compare(">")) ui->pushButtonPlay->setText("||");
    else ui->pushButtonPlay->setText(">");

    emit sendToggleStream();
}

void MainWindow::receiveGoToStart()
{
    emit sendGoToStart();
    emit sendUpdateFrame();
}

void MainWindow::receiveNext()
{
    emit sendNext();
    emit sendUpdateFrame();
}

void MainWindow::receivePrevious()
{
    emit sendPrevious();
    emit sendUpdateFrame();
}

void MainWindow::on_horizontalSliderVideoSpeed_valueChanged(int value)
{
    ui->labelVideoSpeed->setText( QString::number( value*0.1 ) + "%" );
    emit sendVideoFrameInterval( (2 - value * 0.001) * 1000 / 60 );
}

void MainWindow::on_horizontalSliderVideoPosition_sliderPressed()
{
    emit sendToggleStream();
}

void MainWindow::on_horizontalSliderVideoPosition_sliderReleased()
{
    emit sendGoTo( ui->horizontalSliderVideoPosition->value() );
    emit sendToggleStream();
}

void MainWindow::on_actionOpenGame_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), "D:/Videos/", tr("Video Files ( *.mp4)"));

    emit sendOpenVideoFile( filename );
}

void MainWindow::on_actionNewSeason_triggered()
{
    season.SetName("2016/2017");
    season.SetFilename("filename");
}

void MainWindow::on_actionSave_triggered()
{
    cv::FileStorage fs(season.GetFilename().toStdString(), cv::FileStorage::WRITE);
    fs << "season" << season;
    fs.release();
}

void MainWindow::on_actionOpenSeason_triggered()
{
    cv::FileStorage fs("D:/Videos/store.yaml", cv::FileStorage::READ);
    QString temp = QString::fromStdString( fs["name"] );
    qDebug() << "name: " << temp;
}

void MainWindow::on_actionSaisonAnsicht_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionSpielAnsicht_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonOpenSeasonFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Öffne Saison File"), "D:/Videos/", tr("YAML Files ( *.yaml)"));
    ui->lineEditSeasonFilename->setText(filename);
    season.SetFilename(filename);

    cv::FileStorage fs;
    fs.open(filename.toStdString(), cv::FileStorage::READ);

    fs["season"] >> season;
    ui->lineEditSeasonName->setText(season.GetName());

}

void MainWindow::on_pushButtonNewGame_clicked()
{
    // TODO:
//    game.setGame(ui->tableWidgetGames->rowCount()+1,
//                 Team::Team("Heimmannschaft"),
//                 Team::Team("Gastmannschaft"),
//                 {});
//    season.AddGame(game);
//
//    ui->tableWidgetGames->setRowCount( ui->tableWidgetGames->rowCount()+1);
//    ui->tableWidgetGames->setItem(
//            ui->tableWidgetGames->rowCount()-1, 0, new QTableWidgetItem( game.GetHomeTeam().GetName() ) );
//    ui->tableWidgetGames->setItem(
//            ui->tableWidgetGames->rowCount()-1, 1, new QTableWidgetItem( game.GetGuestTeam().GetName() ) );
//    ui->tableWidgetGames->setCurrentCell(ui->tableWidgetGames->rowCount()-1,0);
}

void MainWindow::on_tableWidgetGames_doubleClicked(const QModelIndex &index)
{
    game = season.GetGame(index.row());
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_lineEditSeasonName_textChanged(const QString &arg1)
{
    season.SetName(arg1);
}

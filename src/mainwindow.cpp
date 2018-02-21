//
// Created by hannes on 18.02.18.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui_{new Ui::MainWindow}
{
    ui_->setupUi(this);
    Setup();
    ui_->stackedWidget_2->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    thread_->quit();
    while (!thread_->isFinished())
        ;

    delete thread_;
    delete ui_;
}

void MainWindow::Setup()
{
    thread_ = new QThread();
    auto* worker = new OpenCvWorker();
    worker_trigger_ = new QTimer();
    worker_trigger_->setInterval(1000 / 60);

    connect(worker_trigger_, SIGNAL(timeout()), worker, SLOT(ReceiveGrabFrame()));
    connect(thread_, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread_, SIGNAL(finished()), worker_trigger_, SLOT(deleteLater()));
    connect(this, SIGNAL(SendOpenVideoFile(QString)), worker, SLOT(ReceiveOpenVideoFile(QString)));
    connect(this, SIGNAL(SendToggleStream()), worker, SLOT(ReceiveToggleStream()));
    connect(ui_->pushButtonPlay, SIGNAL(clicked(bool)), this, SLOT(ReceiveToggleStream()));
    connect(ui_->pushButtonGoToStart, SIGNAL(clicked(bool)), this, SLOT(ReceiveGoToStart()));
    connect(this, SIGNAL(SendGoToStart()), worker, SLOT(ReceiveGoToStart()));
    connect(this, SIGNAL(SendUpdateFrame()), worker, SLOT(ReceiveUpdateFrame()));
    connect(this, SIGNAL(SendGrabFrame()), worker, SLOT(ReceiveGrabFrame()));
    connect(ui_->pushButtonNext, SIGNAL(clicked(bool)), this, SLOT(ReceiveNext()));
    connect(this, SIGNAL(SendNext()), worker, SLOT(ReceiveNext()));
    connect(ui_->pushButtonPrevious, SIGNAL(clicked(bool)), this, SLOT(ReceivePrevious()));
    connect(this, SIGNAL(SendPrevious()), worker, SLOT(ReceivePrevious()));
    connect(worker, SIGNAL(SendFrame(QImage)), this, SLOT(ReceiveFrame(QImage)));
    connect(thread_, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread_, SIGNAL(finished()), worker_trigger_, SLOT(deleteLater()));
    connect(worker, SIGNAL(SendVideoEndTime(QTime)), this, SLOT(ReceiveVideoEndTime(QTime)));
    connect(worker, SIGNAL(SendVideoFrameCount(int)), this, SLOT(ReceiveVideoFrameCount(int)));
    connect(worker, SIGNAL(SendVideoCurrentTime(QTime)), this, SLOT(ReceiveVideoCurrentTime(QTime)));
    connect(worker, SIGNAL(SendVideoCurrentFrameNumber(int)), this, SLOT(ReceiveVideoCurrentFrameNumber(int)));
    connect(this, SIGNAL(SendGoTo(int)), worker, SLOT(ReceiveGoTo(int)));
    connect(this, SIGNAL(SendVideoFrameInterval(int)), worker_trigger_, SLOT(start(int)));

    worker_trigger_->start();
    worker->moveToThread(thread_);
    worker_trigger_->moveToThread(thread_);

    thread_->start();
}

void MainWindow::ReceiveFrame(QImage frame)
{
    ui_->labelViewVideo->setPixmap(QPixmap::fromImage(frame));
}

void MainWindow::ReceiveVideoEndTime(QTime video_end_time)
{
    ui_->labelVideoLength->setText(video_end_time.toString("H:mm:ss"));
}

void MainWindow::ReceiveVideoFrameCount(int video_frame_count)
{
    ui_->horizontalSliderVideoPosition->setMaximum(video_frame_count);
}

void MainWindow::ReceiveVideoCurrentTime(QTime video_current_time)
{
    ui_->labelVideoPosition->setText(video_current_time.toString("H:mm:ss"));
}

void MainWindow::ReceiveVideoCurrentFrameNumber(int video_current_frame_number)
{
    ui_->horizontalSliderVideoPosition->setValue(video_current_frame_number);
}

void MainWindow::ReceiveToggleStream()
{
    if (!ui_->pushButtonPlay->text().compare(">"))
        ui_->pushButtonPlay->setText("||");
    else
        ui_->pushButtonPlay->setText(">");

    emit SendToggleStream();
}

void MainWindow::ReceiveGoToStart()
{
    emit SendGoToStart();
    emit SendUpdateFrame();
}

void MainWindow::ReceiveNext()
{
    emit SendNext();
    emit SendUpdateFrame();
}

void MainWindow::ReceivePrevious()
{
    emit SendPrevious();
    emit SendUpdateFrame();
}

void MainWindow::on_horizontalSliderVideoSpeed_valueChanged(int value)
{
    ui_->labelVideoSpeed->setText(QString::number(value * 0.1) + "%");
    emit SendVideoFrameInterval((2 - value * 0.001) * 1000 / 60);
}

void MainWindow::on_horizontalSliderVideoPosition_sliderPressed()
{
    emit SendToggleStream();
}

void MainWindow::on_horizontalSliderVideoPosition_sliderReleased()
{
    emit SendGoTo(ui_->horizontalSliderVideoPosition->value());
    emit SendToggleStream();
}

void MainWindow::on_actionOpenGame_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), "D:/Videos/", tr("Video Files ( *.mp4)"));

    emit SendOpenVideoFile(filename);
}

void MainWindow::on_actionNewSeason_triggered()
{
    season.SetName("2016/2017");
    season.SetFilename("filename");
}

void MainWindow::on_actionSave_triggered()
{
    cv::FileStorage file_storage(season.GetFilename().toStdString(), cv::FileStorage::WRITE);
    file_storage << "season" << season;
    file_storage.release();
}

void MainWindow::on_actionOpenSeason_triggered()
{
    cv::FileStorage file_storage("D:/Videos/store.yaml", cv::FileStorage::READ);
    QString temp = QString::fromStdString(file_storage["name"]);
    qDebug() << "name: " << temp;
}

void MainWindow::on_actionSaisonAnsicht_triggered()
{
    ui_->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionSpielAnsicht_triggered()
{
    ui_->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonOpenSeasonFile_clicked()
{
    QString filename =
        QFileDialog::getOpenFileName(this, tr("Öffne Saison File"), "D:/Videos/", tr("YAML Files ( *.yaml)"));
    ui_->lineEditSeasonFilename->setText(filename);
    season.SetFilename(filename);

    cv::FileStorage file_storage;
    file_storage.open(filename.toStdString(), cv::FileStorage::READ);

    file_storage["season"] >> season;
    ui_->lineEditSeasonName->setText(season.GetName());
}

void MainWindow::on_pushButtonNewGame_clicked()
{
    Game game{ui_->tableWidgetGames->rowCount() + 1, Team{"Heimmannschaft"}, Team{"Gastmannschaft"}, {}, {}};
    season.AddGame(game);

    ui_->tableWidgetGames->setRowCount(ui_->tableWidgetGames->rowCount() + 1);
    ui_->tableWidgetGames->setItem(
        ui_->tableWidgetGames->rowCount() - 1, 0, new QTableWidgetItem( game.GetHomeTeam().GetName()) );
    ui_->tableWidgetGames->setItem(
        ui_->tableWidgetGames->rowCount() - 1, 1, new QTableWidgetItem(game.GetGuestTeam().GetName()));
    ui_->tableWidgetGames->setCurrentCell(ui_->tableWidgetGames->rowCount() - 1, 0);
}

void MainWindow::on_tableWidgetGames_doubleClicked(const QModelIndex& index)
{
    game = season.GetGame(index.row());
    ui_->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_lineEditSeasonName_textChanged(const QString& arg1)
{
    season.SetName(arg1);
}

//
// Created by hannes on 22.02.18.
//

#include <QtTest/qtestkeyboard.h>
#include "../mainwindow.h"
#include <QtTest/QtTest>
#include <QtWidgets/QtWidgets>

class MainWindowSpec : public QObject
{
    Q_OBJECT

  private slots:
    void Constructor();
    void SeasonName();

  private:
    MainWindow unit_;
};

void MainWindowSpec::Constructor() {
//    QVERIFY(unit_.thread_->isRunning());
//    QVERIFY(unit_.worker_trigger_->isActive());
//    QCOMPARE(unit_.worker_trigger_->interval(), 1000 / 60);
}

void MainWindowSpec::SeasonName() {
    //QTest::keyClicks( , "2015/2016");
    //QCOMPARE("2015/2016", unit_.ui_ .lineEditSeasonName);
}

QTEST_MAIN(MainWindowSpec)
//#include "mainwindow_spec.moc"

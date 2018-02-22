//
// Created by hannes on 22.02.18.
//

#include <QtTest/QtTest>
#include <QtWidgets/QtWidgets>
#include <QtTest/qtestkeyboard.h>

class MainWindowSpec : public QObject
{
    Q_OBJECT

  private slots:
    void t1() {QVERIFY(true); };
    void t2();
};

void MainWindowSpec::t2()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_MAIN(MainWindowSpec)
#include "mainwindow_spec.moc"

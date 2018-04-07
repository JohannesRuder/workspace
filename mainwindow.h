#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>  // for QMainWindow
#include <qobjectdefs.h>  // for Q_OBJECT
#include <qstring.h>      // for QString

class QObject;
class QWidget;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H

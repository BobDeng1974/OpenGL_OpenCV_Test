#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cvwrapper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void update_cam_display(QImage img);

    void on_btn_start_clicked();
    void on_btn_stop_clicked();

private:
    Ui::MainWindow *ui;
    CVWrapper m_wrapper;
};

#endif // MAINWINDOW_H

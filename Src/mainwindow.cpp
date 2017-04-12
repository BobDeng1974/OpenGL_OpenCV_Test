#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_wrapper,SIGNAL(new_frame(QImage)),this,SLOT(update_cam_display(QImage)));
    connect(&m_wrapper,SIGNAL(new_frame(cv::Mat)),ui->openGLWidget,SLOT(update_texture(cv::Mat)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_cam_display(QImage img)
{
    ui->camera_img_label->setPixmap(QPixmap::fromImage(img,Qt::AutoColor));
}

void MainWindow::on_btn_start_clicked()
{
    if(m_wrapper.OpenCamera())
    {

    }

}

void MainWindow::on_btn_stop_clicked()
{
   m_wrapper.CloseCamera();

   QPixmap black_image = *ui->camera_img_label->pixmap();

   black_image.fill(Qt::black);

   ui->camera_img_label->setPixmap(black_image);
}

#include "cvwrapper.h"

CVWrapper::CVWrapper(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(acquire_frame()));
}

bool CVWrapper::OpenCamera()
{
    m_webcam = new cv::VideoCapture(0);

    if(m_webcam->isOpened())
    {
       m_timer->start(CAM_REFRESH_MS);
    }

    return m_webcam->isOpened();
}

bool CVWrapper::CloseCamera()
{
    if(m_webcam->isOpened())
    {
        m_timer->stop();
        m_webcam->release();
    }

    return m_webcam->isOpened();
}

void CVWrapper::acquire_frame()
{
    bool frame_readed_successfully = m_webcam->read(m_cam_img);

    if(!frame_readed_successfully || m_cam_img.empty())
    {
        qDebug()<<"Frame drop!";
    }

    m_cam_qimg = Mat2QImage(m_cam_img);

    //Update frame
    new_frame(m_cam_qimg);
    new_frame(m_cam_img);
}

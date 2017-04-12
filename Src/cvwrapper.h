#ifndef CVWRAPPER_H
#define CVWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QTimer>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#define CAM_REFRESH_MS 10

class CVWrapper : public QObject
{
    Q_OBJECT

public:
    explicit CVWrapper(QObject *parent = 0);

    bool OpenCamera();
    bool CloseCamera();

signals:
    void new_frame(QImage  img);
    void new_frame(cv::Mat img);

public slots:
    void acquire_frame();

private:

    //Helper methods
    QImage Mat2QImage(cv::Mat const& src)
    {
         cv::Mat temp; // make the same cv::Mat
         cv::cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
         QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
         dest.bits(); // enforce deep copy, see documentation
         // of QImage::QImage ( const uchar * data, int width, int height, Format format )
         return dest;
    }

    cv::Mat QImage2Mat(QImage const& src)
    {
         cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
         cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
         cv::cvtColor(tmp, result,CV_BGR2RGB);
         return result;
    }

    //Variables
    QTimer* m_timer;
    cv::VideoCapture* m_webcam;
    cv::Mat m_cam_img;
    QImage m_cam_qimg;

};

#endif // CVWRAPPER_H

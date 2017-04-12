#include "mopenglwidget.h"

MOpenGLWidget::MOpenGLWidget(QWidget *parent):QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    cam.rotX=18.50;
    cam.rotY=-45.0;
    cam.rotZ=  0.0;
    cam.posZ=-7.0;

    create_texture = true;

    //this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void MOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1.0);

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 

    glEnable(GL_TEXTURE_2D);


}

void MOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    glFrustum(-x, x, -x, x, 3, 50);
    glMatrixMode(GL_MODELVIEW);
}

void MOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, cam.posZ);
    glRotatef(cam.rotX, 1.0, 0.0, 0.0);
    glRotatef(cam.rotY, 0.0, 1.0, 0.0);
    glRotatef(cam.rotZ, 0.0, 0.0, 1.0);

    /*All drawing goes here */

//    drawFloorGrid(2.5);
//    drawXYZ(0.75);

    drawPolygon();
}

void MOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    cam.lastPos = event->pos();
}

void MOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - cam.lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - cam.lastPos.y()) / height();

    if(event->buttons() & Qt::LeftButton) {
        cam.rotX += 180 * dy;
        cam.rotY += 180 * dx;
        updateGL();
    } else if(event->buttons() & Qt::RightButton) {
        cam.rotX += 180 * dy;
        cam.rotZ += 180 * dx;
        updateGL();
    }

    cam.lastPos = event->pos();
}

void MOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    cam.posZ+=((float)event->delta())*0.01;
    updateGL();
    event->accept();
}

void MOpenGLWidget::drawFloorGrid(GLfloat size)
{
    glColor3f(0.80, 0.80,0.80);
    glBegin(GL_LINES);

    for (GLfloat i = -size; i <= size; i += 0.25)
    {
      glVertex3f(i, 0, -size); glVertex3f(i, 0, size);
      glVertex3f(size, 0, i); glVertex3f(-size, 0, i);
    }

    glEnd();
}

void MOpenGLWidget::drawXYZ(GLfloat axisLength)
{
    GLfloat offset=0.01;

    glLineWidth(3.0);

    glBegin(GL_LINES);
    qglColor(Qt::red);
    glVertex3f(offset,offset,offset);
    glVertex3f(axisLength,offset,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::green);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,axisLength,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::blue);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,offset,axisLength);
    glEnd();

    glLineWidth(1.0);
}

void MOpenGLWidget::drawPolygon()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frame_texture);

    glColor3f(1,1,1); // set global color to white, otherwise this color will be (somehow) added to the texture

    glBegin(GL_QUADS);

    float x = 3.0;
    float y = 3.0;

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x, -y, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x, y, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y, 0.0f);

    glEnd();
}

void MOpenGLWidget::setCameraFront()
{
    cam.rotX=0;
    cam.rotY=0;
    cam.rotZ=0;
    updateGL();
}

void MOpenGLWidget::setCameraBack()
{
    cam.rotX=0;
    cam.rotY=180;
    cam.rotZ=0;
    updateGL();
}

void MOpenGLWidget::setCameraTop()
{
    cam.rotX=90;
    cam.rotY=0;
    cam.rotZ=0;
    updateGL();
}

void MOpenGLWidget::setCameraBottom()
{
    cam.rotX=-90;
    cam.rotY=0;
    cam.rotZ=0;
    updateGL();
}

void MOpenGLWidget::setCameraDefault()
{
    cam.rotX=18.50;
    cam.rotY=-45.0;
    cam.rotZ=0.0;
    cam.posZ=-15.0;
    updateGL();
}

void MOpenGLWidget::update_texture(cv::Mat img)
{
    cv::Mat tx_img;

    //Flip image
    cv::flip(img,tx_img,0);

    qDebug()<<"Image fliped";

    //Get bytes from image
    int img_size = tx_img.total() * tx_img.elemSize();

    GLsizei width  = tx_img.cols;
    GLsizei height = tx_img.rows;

    byte* img_bytes = (byte*) malloc(img_size*sizeof(byte));
    std::memcpy(img_bytes,tx_img.data,img_size * sizeof(byte));

    //Create texture only first time
    if(create_texture)
    {
        qDebug()<<"Creating texture...";

        glGenTextures(1, &frame_texture);
        create_texture = false;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,frame_texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, img_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    qDebug()<<"Texture created! Clearing image bytes...";

    free(img_bytes);

    updateGL();
}



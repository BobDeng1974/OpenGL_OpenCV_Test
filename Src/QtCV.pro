#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T13:07:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    cvwrapper.cpp \
    mopenglwidget.cpp

HEADERS  += mainwindow.h \
    cvwrapper.h \
    mopenglwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:\\Instalacije\\opencv\\build\\include

LIBS+= -LD:\\Instalacije\\opencv\\mybuild\\lib\Debug \
-lopencv_core320d \
-lopencv_highgui320d \
-lopencv_imgproc320d \
-lopencv_ml320d \
-lopencv_objdetect320d \
-lopencv_imgcodecs320d \
-lopencv_photo320d \
-lopencv_shape320d \
-lopencv_stitching320d \
-lopencv_superres320d \
-lopencv_ts320d \
-lopencv_video320d \
-lopencv_videoio320d \
-lopencv_videostab320d \
-lopencv_calib3d320d \
-lopencv_core320d \
-lopencv_features2d320d \
-lopencv_flann320d \
-lopencv_highgui320d \

LIBS+= -lopengl32

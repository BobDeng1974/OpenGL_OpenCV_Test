# OpenCV OpenGL test

This is test application made in Qt as example how to use OpenCV camera feed as texture in OpenGL. 

**What is used in this test**
* OpenCV 3.0 
* OpenGL 
* QT Creator 4.2.0 based on Qt 5.7.1
* Windows PC

**Project configuration**

*WINDOWS CONFIGURATION:*

1. INCLUDEPATH = \\opencv\\build\\include folder 
2. LIBS+ = \\opencv\\build\\lib\\Debug \* **- FOR DEBUG** or \\lib\\Release \* **- FOR RELEASE**
3. LIBS+ = -lopengl32 **- WINDOWS OPENGL**

*LINUX CONFIGURATION:*

1. INCLUDEPATH += /usr/local/include/opencv **- DEFAULT OPENCV LINUX PATH**
2. LIBS += -L/usr/local/lib \*    
3. LIBS += -lGL **- LINUX OPENGL LIB**


# Screenshot on Windows 

![Windows](/images/Screenshot.jpg?raw=true "OpenGL OpenCV camera feed texture test")

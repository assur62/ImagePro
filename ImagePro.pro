#-------------------------------------------------
#
# Project created by QtCreator 2018-08-01T13:48:28
#
#-------------------------------------------------

QT       += core gui charts datavisualization


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImProc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp


SOURCES += \
        main.cpp \
        mainwindow.cpp


HEADERS += \
        mainwindow.h \

FORMS += \
        mainwindow.ui

DISTFILES +=

win32: LIBS += -L$$PWD/./ -lfftw3-3

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

INCLUDEPATH += C:\opencv\build\include
#INCLUDEPATH += C:\opencv\build\include\opencv
#INCLUDEPATH += C:\opencv\build\include\opencv2

LIBS += C:\opencv-build\bin\libopencv_core345.dll
LIBS += C:\opencv-build\bin\libopencv_highgui345.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs345.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc345.dll
LIBS += C:\opencv-build\bin\libopencv_features2d345.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d345.dll

LIBS += C:\opencv-build\bin\libopencv_video345.dll
LIBS += C:\opencv-build\bin\opencv_videoio345.dll


RESOURCES += \
    Images/images.qrc \
    pentagrams.qrc

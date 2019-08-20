QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoProcessor
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        capturethread.cpp \
        kalmanfilter.cpp

HEADERS += \
        mainwindow.h \
        capturethread.h \
        functions.h \
        kalmanfilter.h

FORMS += \
        mainwindow.ui

#include($$PWD/opencv.pri)

LIBS += -L$$(OPENCV_DIR)/opencv-4.1.1/x64/vc15/lib/ -lopencv_world411
LIBS += -L$$(OPENCV_DIR)/opencv-4.1.1/x64/vc15/lib/ -lopencv_world411d
INCLUDEPATH += $$(OPENCV_DIR)/opencv-4.1.1/include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

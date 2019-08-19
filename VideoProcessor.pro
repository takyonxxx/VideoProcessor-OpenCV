QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoProcessor
TEMPLATE = app

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

win32: LIBS += -L$$(OPENCV_DIR)/build/x64/vc15/lib/ -lopencv_world411
INCLUDEPATH += $$(OPENCV_DIR)/build/include

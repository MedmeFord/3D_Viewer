QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brain.c \
    main.cpp \
    mainwindow.cpp \
    matrix.c \
    widget.cpp

HEADERS += \
    brain.h \
    mainwindow.h \
    widget.h

FORMS += \
    mainwindow.ui \
    widget.ui

include (../QtGifImage-master/src/gifimage/qtgifimage.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QtGifImage-master/src/gifimage/qtgifimage.pri \
    cube.obj

SUBDIRS += \
    ../../../../Downloads/C8_3DViewer_v1.0-0/QtGifImage-master/qtgifimage.pro \
    ../../QtGifImage-master/qtgifimage.pro \
    ../../QtGifImage-master/qtgifimage.pro \
    ../../QtGifImage-master/qtgifimage.pro \
    ../../QtGifImage-master/qtgifimage.pro \
    ../QtGifImage-master/qtgifimage.pro \
    QtGifImage-master/qtgifimage.pro \
    QtGifImage-master/qtgifimage.pro \
    QtGifImage-master/src/src.pro

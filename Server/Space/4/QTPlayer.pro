QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include

LIBS +=  $$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
         $$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
         $$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
         $$PWD/ffmpeg-4.2.2/lib/avformat.lib\
         $$PWD/ffmpeg-4.2.2/lib/avutil.lib\
         $$PWD/ffmpeg-4.2.2/lib/postproc.lib\
         $$PWD/ffmpeg-4.2.2/lib/swresample.lib\
         $$PWD/ffmpeg-4.2.2/lib/swscale.lib

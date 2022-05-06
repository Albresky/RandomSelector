QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileOperator.cpp \
    aboutwindow.cpp \
    commonHeaders.cpp \
    config.cpp \
    functions.cpp \
    main.cpp \
    mainwindow.cpp \
    numpool.cpp

HEADERS += \
    FileOperator.h \
    aboutwindow.h \
    commonHeaders.h \
    config.h \
    functions.h \
    mainwindow.h \
    numpool.h

FORMS += \
    aboutWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = $$PWD/res/icon.ico

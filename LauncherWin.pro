#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T22:16:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LauncherWin
TEMPLATE = app

#QMAKE_CXXFLAGS += -Weffc++

SOURCES += src/main.cpp\
    src/core/controller.cpp \
    src/core/trayicon.cpp \
    src/core/hotkeycapturer.cpp \
    src/unused/containscompleter.cpp \
    src/main/mainwindow.cpp \
    src/main/googleresultdelegate.cpp \
    src/main/queryworker.cpp \
    src/main/argumenteditor.cpp \
    src/edit/optionsdialog.cpp \
    src/util/persistencehandler.cpp \
    src/edit/hotkeyeditor.cpp

HEADERS  += src/core/controller.h \
    src/core/trayicon.h \
    src/core/hotkeycapturer.h \
    src/unused/containscompleter.h \
    src/main/mainwindow.h \
    src/main/googleresultdelegate.h \
    src/main/queryworker.h \
    src/main/argumenteditor.h \
    src/edit/optionsdialog.h \
    src/util/target.h \
    src/util/persistencehandler.h \
    src/util/constants.h \
    src/edit/hotkeyeditor.h

FORMS    += ui/mainwindow.ui \
    ui/optionsdialog.ui

RC_FILE = LauncherWin.rc
RESOURCES = res/trayIcon.qrc \
    res/editIcons.qrc

OTHER_FILES += \
    ToDo.txt

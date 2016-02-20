#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T22:16:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lunger
TEMPLATE = app

include("../../Windows/Libraries/QBorderLayout/QBorderLayout.pri")

#QMAKE_CXXFLAGS += -Weffc++
QMAKE_CXXFLAGS_RELEASE -= -O2 -O1
QMAKE_CXXFLAGS_RELEASE += -O3 -flto
QMAKE_LFLAGS_RELEASE -= -O1 -O2 -O3

SOURCES += src/main.cpp\
    src/core/controller.cpp \
    src/core/trayicon.cpp \
    src/core/hotkeycapturer.cpp \
    src/main/mainwindow.cpp \
    src/main/googleresultdelegate.cpp \
    src/main/queryworker.cpp \
    src/util/persistencehandler.cpp \
    src/edit/optionsdialog.cpp \
    src/edit/hotkeyeditor.cpp \
    src/view/argumenteditor.cpp \
    src/util/target.cpp
    #src/view/borderlayout.cpp

HEADERS  += src/core/controller.h \
    src/core/trayicon.h \
    src/core/hotkeycapturer.h \
    src/main/mainwindow.h \
    src/main/googleresultdelegate.h \
    src/main/queryworker.h \
    src/util/target.h \
    src/util/persistencehandler.h \
    src/util/constants.h \
    src/edit/optionsdialog.h \
    src/edit/hotkeyeditor.h \
    src/view/argumenteditor.h
    #src/view/borderlayout.h

win32|win64 {
    SOURCES += src/main/mainwindow_win.cpp
}
macx {
    SOURCES += src/main/mainwindow_mac.cpp
} else:unix{
    SOURCES += src/main/mainwindow_unix.cpp
}

FORMS    += ui/mainwindow.ui \
    ui/optionsdialog.ui

RC_FILE = Lunger.rc
RESOURCES = res/trayIcon.qrc \
    res/editIcons.qrc \
    res/config.qrc

OTHER_FILES += \
    ToDo.txt

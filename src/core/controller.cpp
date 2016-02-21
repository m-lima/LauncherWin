#include "controller.h"

#include <QApplication>
#include <QProcess>

#include "../util/constants.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{

    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        tray = new TrayIcon(QIcon(RES_TRAY), this);
        connect(tray, SIGNAL(close()), this, SLOT(closeApp()));
        connect(tray, SIGNAL(open()), this, SLOT(trayOpen()));
        connect(tray, SIGNAL(edit()), this, SLOT(edit()));
    } else {
        tray = NULL;
    }

    capturer = new HotkeyCapturer(this);
    connect(capturer, SIGNAL(hotkeyPressed(QString)), this, SLOT(launch(QString)));
}

Controller::~Controller()
{
    delete tray;
    capturer->setActive(false);
    delete capturer;
}

void Controller::initialize()
{
    if (tray) tray->show();
    capturer->setActive(true);
}

void Controller::finalize()
{
    capturer->setActive(false);

    if (tray) {
        tray->hide();
    }

    qApp->exit();
}

void Controller::launch(QString target)
{
    if (target == CAPTURE_PAUSE) {
        capturer->togglePaused();
    } else {
        QProcess process(this);
        process.startDetached(QCoreApplication::applicationFilePath(), QStringList(target));
    }
}

void Controller::trayOpen()
{
    launch("");
}

void Controller::closeApp()
{
    finalize();
}

void Controller::edit()
{
    capturer->setActive(false);
    QStringList arguments;
    arguments.append("edit");
    arguments.append("window");
    QProcess *process = new QProcess(this);
    process->start(QCoreApplication::applicationFilePath(), arguments);
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(editClosed(int))); //Clean UP!!
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), process, SLOT(deleteLater())); //Clean UP!!
}

void Controller::editClosed(int code)
{
    capturer->setActive(true);
//    if (code == MAIN_EDIT_SAVE) {
//    }
}

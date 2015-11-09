#include "controller.h"

#include <QApplication>
#include <QProcess>

#include "../util/constants.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    paused = false;

    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        tray = new TrayIcon(QIcon(IMG_TRAY), this);
        connect(tray, SIGNAL(close()), this, SLOT(closeApp()));
        connect(tray, SIGNAL(open()), this, SLOT(trayOpen()));
        connect(tray, SIGNAL(edit()), this, SLOT(edit()));
    } else {
        tray = NULL;
    }

    capturer = NULL;
    setCapturerActive(true);
}

Controller::~Controller()
{
    delete tray;
    delete capturer;
}

void Controller::initialize()
{
    if (tray) tray->show();
}

void Controller::finalize()
{
    setCapturerActive(false);

    if (tray) {
        tray->hide();
        tray->deleteLater();
    }

    exit(0);
}

void Controller::setCapturerActive(bool active)
{
    if (active) {
        if (capturer == NULL) {
            capturer = new HotkeyCapturer(paused);
            capturer->moveToThread(capturer);
            connect(capturer, SIGNAL(hotkeyPressed(QString)), SLOT(launch(QString)));
            capturer->start();
        }
    } else {
        if (capturer) {
            capturer->deactivate();
            delete capturer;
            capturer = NULL;
        }
    }
}

void Controller::launch(QString target)
{
    if (target == CAPTURE_PAUSE) {
        setCapturerActive(false);
        paused = !paused;
        setCapturerActive(true);
//    } else if (target == CONSOLE) {
//        QProcess process(this);
//        process.startDetached("C:\\Users\\mflim_000\\Bin\\Console2\\Console.exe");
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
//    capturer->setPaused(true);
    setCapturerActive(false);

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
    if (code == EDIT_SAVE) {
        capturer->reload();
    }

    setCapturerActive(true);
//    disconnect(
//    capturer->setPaused(false);
    //q/Debug() << "Finished: " << QString::number(code);
}

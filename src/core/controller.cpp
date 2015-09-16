#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        tray = new TrayIcon(QIcon(IMG_TRAY), this);
        connect(tray, SIGNAL(close()), this, SLOT(closeApp()));
        connect(tray, SIGNAL(open()), this, SLOT(trayOpen()));
        connect(tray, SIGNAL(edit()), this, SLOT(edit()));
    } else {
        tray = NULL;
    }

    capturer = new HotkeyCapturer();
    capturer->moveToThread(capturer);
    connect(capturer, SIGNAL(hotkeyPressed(QString)), SLOT(launch(QString)));
}

Controller::~Controller()
{
    delete tray;
    delete capturer;
}

void Controller::initialize()
{
    if (tray) tray->show();
    capturer->start();
}

void Controller::finalize()
{
    capturer->deactivate();
    capturer->deleteLater();

    if (tray) {
        tray->hide();
        tray->deleteLater();
    }

    exit(0);
}

void Controller::launch(QString target)
{
    QProcess process(this);
    process.startDetached(QCoreApplication::applicationFilePath(), QStringList(target));
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
    capturer->setPaused(true);

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
    capturer->setPaused(false);
    qDebug() << "Finished: " << QString::number(code);
}

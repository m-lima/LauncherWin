#include <QApplication>
#include <QStyleFactory>
#include <QObject>
#include <QDesktopWidget>
#include <QSharedMemory>
#include <QLocalSocket>
#include <QTime>

#include "core/controller.h"
#include "main/mainwindow.h"
#include "edit/optionsdialog.h"
#include "util/constants.h"
#include "util/persistencehandler.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    int WIDTH = widget.width();
    int HEIGHT = widget.height();

    QDesktopWidget *desktop = QApplication::desktop(); //How should I delete this

    screenWidth = desktop->screen()->width();
    screenHeight = desktop->screen()->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    widget.setGeometry(x, y, WIDTH, HEIGHT);
    widget.setFixedSize(WIDTH, HEIGHT);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QCoreApplication::setOrganizationName(MAIN_ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(MAIN_ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(MAIN_APPLICATION_NAME);

    //If no arguments, this is the main controller
    if (argc < 2) {

        QSharedMemory shared(MAIN_SHARED_MEMORY);
        if (!shared.create(512, QSharedMemory::ReadWrite)) {
            if (shared.attach(QSharedMemory::ReadWrite)) {
                shared.detach();
                exit(0);
            }
            exit(0);
        }

        qApp->setQuitOnLastWindowClosed(false);

        Controller controller;
        controller.initialize();

        int result = a.exec();

        controller.finalize();

        return result;

    //Edit mode (any two parameters)
    } else if (argc == 3){
        QLocalSocket *socket = new QLocalSocket();
        socket->connectToServer(SERVER_EDIT);

        QTime *time = new QTime();
        time->start();
        QList<Target *> *targets = PersistenceHandler::loadTargets(true);

        if (socket->waitForConnected(100 - time->elapsed())) {
            socket->write(argv[1], strlen(argv[1]));
            socket->flush();
            socket->waitForBytesWritten(5000);
            socket->disconnectFromServer();
            socket->close();
            delete time;
            delete socket;
            exit(0);
        }

        socket->close();
        delete socket;
        delete time;

        OptionsDialog optionsDialog(targets);
        delete targets;

        center(optionsDialog);
        optionsDialog.show();

        return a.exec();

    } else {
        QLocalSocket *socket = new QLocalSocket();
        socket->connectToServer(SERVER_MAIN);

        QTime *time = new QTime();
        time->start();
        QList<Target *> *targets = PersistenceHandler::loadTargets();

        if (socket->waitForConnected(100 - time->elapsed())) {
            socket->write(argv[1], strlen(argv[1]));
            socket->flush();
            socket->waitForBytesWritten(5000);
            socket->disconnectFromServer();
            socket->close();
            delete time;
            delete socket;
            exit(0);
        }

        socket->close();
        delete socket;
        delete time;

        MainWindow mainWindow(targets, argv[1]);

        center(mainWindow);
        mainWindow.show();

        return a.exec();
    }
}

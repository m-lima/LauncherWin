#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "trayicon.h"
#include "hotkeycapturer.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    void initialize();
    void finalize();

private:
    bool paused;
    TrayIcon *tray;
    HotkeyCapturer *capturer;

    void setCapturerActive(bool);

private slots:
    void launch(QString);
    void trayOpen();
    void closeApp();
    void edit();
    void editClosed(int code);
};

#endif // CONTROLLER_H

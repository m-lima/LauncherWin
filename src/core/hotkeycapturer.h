#ifndef HOTKEYCAPTURER_H
#define HOTKEYCAPTURER_H

#include <QThread>
#include <QStringList>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QSharedMemory>
#include "windows.h"


#include <QDebug>


#include "../util/constants.h"
#include "../util/persistencehandler.h"

class HotkeyCapturer : public QThread
{
    Q_OBJECT
public:
    explicit HotkeyCapturer(QObject *parent = 0);
    ~HotkeyCapturer();
    void run() Q_DECL_OVERRIDE;

private:
    bool active;
    bool paused;
    QSharedMemory shared;
    QStringList hotkeys;

    void registerHotkeys();
    void unregisterHotkeys();
    
signals:
    void hotkeyPressed(QString);
    
public slots:
    void setPaused(bool paused);
    void deactivate();
    void reload();
    
};

#endif // HOTKEYCAPTURER_H

#ifndef HOTKEYCAPTURER_H
#define HOTKEYCAPTURER_H

#include <QThread>
#include <QStringList>
#include <QSharedMemory>

class HotkeyCapturer : public QThread
{
    Q_OBJECT
public:
    explicit HotkeyCapturer(const bool &paused, QObject *parent = 0);
    ~HotkeyCapturer();
    void run() Q_DECL_OVERRIDE;

private:
    bool active;
    bool paused_;
    //DWORD threadID;
    QSharedMemory shared;
    QStringList hotkeys;

    void registerHotkeys();
    void unregisterHotkeys();
    
signals:
    void hotkeyPressed(QString);
    
public slots:
    //void setPaused(bool paused);
    void deactivate();
    void reload();
    
};

#endif // HOTKEYCAPTURER_H

#ifndef HOTKEYCAPTURER_H
#define HOTKEYCAPTURER_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QStringList>

class HotkeyCapturer : public QObject,  public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit HotkeyCapturer(QObject *parent = 0);
    ~HotkeyCapturer();

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;
    inline void togglePaused() {setPaused(!paused_);}
    inline bool isPaused() const {return paused_;}
    inline void setPaused(bool paused)
    {
        if (paused == paused_) return;
        paused_ = paused;
        reloadHotkeys();
    }
    inline void setActive(bool active)
    {
        if (active == registeredFilter) return;
        if (active) registerHotkeys(true);
        else unregisterHotkeys(true);
        registeredFilter = active;
    }

signals:
    void hotkeyPressed(QString);

private:
    bool paused_;
    bool registeredFilter;
    QStringList hotkeys;

    void registerHotkeys(bool addFilter);
    void unregisterHotkeys(bool removeFilter);
    inline void reloadHotkeys() {unregisterHotkeys(false); registerHotkeys(false);}
};

#endif // HOTKEYCAPTURER_H

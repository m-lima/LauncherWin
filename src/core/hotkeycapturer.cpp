#include "hotkeycapturer.h"
#include "qt_windows.h"
#include <QApplication>

#include "../util/persistencehandler.h"
#include "../util/constants.h"

HotkeyCapturer::HotkeyCapturer(QObject *parent) :
    QObject(parent),
    QAbstractNativeEventFilter()
{
    paused_ = false;
    registeredFilter = false;
}

HotkeyCapturer::~HotkeyCapturer()
{
    setActive(false);
}

bool HotkeyCapturer::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        WPARAM param = msg->wParam;
        if (hotkeys.size() > param) {
            emit hotkeyPressed(hotkeys.at(param));
        }
    }

    return false;
}

void HotkeyCapturer::unregisterHotkeys(bool removeFilter)
{
    if (removeFilter) qApp->removeNativeEventFilter(this);
    for (int i = 0; i < hotkeys.size(); i++) {
        UnregisterHotKey(0, i);
    }

    hotkeys.clear();
}

void HotkeyCapturer::registerHotkeys(bool addFilter)
{
    if (addFilter) qApp->installNativeEventFilter(this);
    int count = 0;

    //Register default hotKey (CTRL + ALT + Space)
    hotkeys.append(CAPTURE_PAUSE);
    RegisterHotKey(0, count, MOD_ALT | MOD_CONTROL | 0x4000, ' ');
    count++;

    if (paused_) return;

    QList<Target *> *targetList = PersistenceHandler::loadTargets(this);
    QStringList split;
    QStringList::iterator splitElement;

    for (QList<Target *>::const_iterator target = targetList->cbegin(); target != targetList->cend(); target++) {
        if (!((*target)->isEnabled()) || (*target)->getHotKey().isEmpty()) {
            continue;
        }

        hotkeys.append((*target)->getName());
        split = (*target)->getHotKey().split(XML_MOD_DIVIDER);
        QChar key = 0;
        QString upper;
        int mods = 0x4000;
        for (splitElement = split.begin();  splitElement != split.end(); splitElement++) {
            upper = (*splitElement).toUpper();
            if ((*splitElement).size() == 1) {
                key = upper.at(0);
            } else {
                if (upper == HOT_SHIFT) {
                    mods |= MOD_SHIFT;
                } else if (upper == HOT_CTRL) {
                    mods |= MOD_CONTROL;
                } else if (upper == HOT_ALT) {
                    mods |= MOD_ALT;
                }
            }
        }

        if (key >= 32 && key <= 126) {
            RegisterHotKey(0, count, mods, key.unicode());
            count++;
        }
    }

    delete targetList;
}


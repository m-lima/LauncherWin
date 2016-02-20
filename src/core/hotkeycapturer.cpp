#include "hotkeycapturer.h"

#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include "windows.h"

#include "../util/constants.h"
#include "../util/persistencehandler.h"

HotkeyCapturer::HotkeyCapturer(bool const &paused, QObject *parent) :
    QThread(parent)
{
    active = false;
    paused_ = paused;
    setTerminationEnabled();
}

HotkeyCapturer::~HotkeyCapturer()
{
    deactivate();
}

void HotkeyCapturer::unregisterHotkeys()
{
    for (int i = 0; i < hotkeys.size(); i++) {
        UnregisterHotKey(0, i);
    }

    hotkeys.clear();
}

//void HotkeyCapturer::setPaused(bool newPaused)
//{
//    if (newPaused && !paused) {
//        unregisterHotkeys();
//        paused = newPaused;
//        return;
//    }

//    if (!newPaused && paused) {
//        registerHotkeys();
//        paused = newPaused;
//        return;
//    }
//}

void HotkeyCapturer::registerHotkeys()
{
    int count = 0;

    //Register default hotKey (CTRL + ALT + Space)
    hotkeys.append(CAPTURE_PAUSE);
    RegisterHotKey(0, count, MOD_ALT | MOD_CONTROL | 0x4000, ' ');
    count++;

    //Workaround for launching Console2
//    hotkeys.append(CONSOLE);
//    RegisterHotKey(0, count, MOD_ALT | MOD_CONTROL | 0x4000, 'L');
//    count++;

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

//    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
//    path.append(FILE_TARGETS);
//    QFile *config = new QFile(path, this);

//    if (config->open(QIODevice::ReadOnly)) {
//        QTextStream stream(config);
//        QString line;
//        QStringList split;

//        while(!stream.atEnd()) {
//             line = stream.readLine().trimmed();

//             if (line.startsWith("#")) {
//                 continue;
//             }

//             split = line.split(';');

//             if (split.size() < 3) {
//                 continue;
//             }

//             hotkeys.append(split.at(0).trimmed());
//             RegisterHotKey(0, count, MOD_ALT | MOD_CONTROL | 0x4000, split.at(2).trimmed().at(0).toUpper().unicode());
//             count++;
//        }

//        config->close();
//    }

//    delete config;
}

void HotkeyCapturer::run() Q_DECL_OVERRIDE
{
    active = true;
    registerHotkeys();

    //threadID = GetCurrentThreadId();

    MSG msg;
    while (active && GetMessage(&msg, NULL, 0, 0) != 0) {
//        if (msg.message == SHUTDOWN_MESSAGE) return;
        if (msg.message == WM_HOTKEY) {
            emit(hotkeyPressed(hotkeys.at(msg.wParam)));
        }
    }
}


void HotkeyCapturer::deactivate()
{
    unregisterHotkeys();
    active = false;
//    PostThreadMessage(threadID, SHUTDOWN_MESSAGE, 0, 0);
    terminate();
}

void HotkeyCapturer::reload()
{
    unregisterHotkeys();
    registerHotkeys();
}

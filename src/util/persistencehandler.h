#ifndef PERSISTENCEHANDLER_H
#define PERSISTENCEHANDLER_H

#include "target.h"

class PersistenceHandler
{
public:
    PersistenceHandler();
    static QList<Target *> *loadTargets(bool fetchDisabled = false, QObject *parent = 0);
    static void saveTargets(QList<Target *> *targets, QObject *parent = 0);
    static void saveHistory(const QString &target, const QStringList &historyList, QObject *parent = 0);
    static void loadHistory(const QString &target, QStringList *historyList, QObject *parent = 0);
    static void loadLast(QString *target, QString *argument, QObject *parent = 0);
    static void saveLast(const QString &target, const QString &argument, QObject *parent = 0);
};

#endif // PERSISTENCEHANDLER_H

#ifndef PERSISTENCEHANDLER_H
#define PERSISTENCEHANDLER_H

#include "target.h"

namespace PersistenceHandler
{
    QList<Target *> *loadTargets(bool fetchDisabled = false, QObject *parent = 0);
    void saveTargets(QList<Target *> *targets, QObject *parent = 0);
    void saveHistory(QString const &target, QStringList const &historyList, QObject *parent = 0);
    void loadHistory(QString const &target, QStringList *historyList, QObject *parent = 0);
    void loadLast(QString *target, QString *argument, QObject *parent = 0);
    void saveLast(QString const &target, QString const  &argument, QObject *parent = 0);
}

#endif // PERSISTENCEHANDLER_H

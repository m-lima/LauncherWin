#ifndef QUERYWORKER_H
#define QUERYWORKER_H

#include <QStringList>

#include <QUrl>
#include <QNetworkReply>

class QueryWorker : public QObject
{
    Q_OBJECT
public:
    explicit QueryWorker(QObject *parent = 0);

signals:
    void queryFinished(QStringList *results);
    void abortRequested();

public slots:
    void abort();
    void query(QString query, QString argument);
    void process(QNetworkReply *reply);
};

#endif // QUERYWORKER_H

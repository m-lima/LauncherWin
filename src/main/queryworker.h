#ifndef QUERYWORKER_H
#define QUERYWORKER_H

#include <QThread>
#include <QStringList>

#include <QUrl>
#include <QNetworkReply>

class QueryWorker : public QThread
{
    Q_OBJECT
public:
    explicit QueryWorker(QString &query, QString &argument, QObject *parent = 0);
    ~QueryWorker();
    void run() Q_DECL_OVERRIDE;

private:
    QUrl *url;
    QNetworkReply *reply;

signals:
    void queryFinished(QStringList *results);
    
public slots:
    void abort();
};

#endif // QUERYWORKER_H

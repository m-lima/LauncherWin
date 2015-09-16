#ifndef QUERYWORKER_H
#define QUERYWORKER_H

#include <QThread>
#include <QStringList>

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QEventLoop>

class QueryWorker : public QThread
{
    Q_OBJECT
public:
    explicit QueryWorker(QString &query, QString &argument, QObject *parent = 0);
    ~QueryWorker();
    void run() Q_DECL_OVERRIDE;

signals:
    void queryFinished(QStringList *results);

    
public slots:
    void abort();

private:
    QUrl *url;
    QNetworkReply *reply;
};

#endif // QUERYWORKER_H

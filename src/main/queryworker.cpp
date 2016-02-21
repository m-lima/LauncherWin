#include "queryworker.h"

#include <QNetworkAccessManager>
#include <QXmlStreamReader>
#include <QEventLoop>

QueryWorker::QueryWorker(QObject *parent) :
    QObject(parent)
{
}

void QueryWorker::query(QString query, QString argument)
{
    QUrl url = QUrl(query + argument);
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);

    QNetworkReply *reply = qnam->get(QNetworkRequest(url));
    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(process(QNetworkReply*)));
    connect(this, SIGNAL(abortRequested()), reply, SLOT(abort()));
}

void QueryWorker::process(QNetworkReply *reply)
{

    if (reply->isOpen() && reply->isReadable()) {
        QXmlStreamReader reader(reply->readAll());

        QStringList *results = new QStringList();
        QString data;
        while (reply->isReadable() && !reader.atEnd()) {
            reader.readNext();
            if (reader.name() == "suggestion") {
                data = reader.attributes().value("data").toString();
                if (!data.isNull() && !data.isEmpty()) {
                    results->append(data + ' ');
                }
            }
        }

        emit queryFinished(results);
    }

    reply->deleteLater();
    reply->manager()->deleteLater();
}

void QueryWorker::abort()
{
    emit abortRequested();
}

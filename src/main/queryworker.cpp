#include "queryworker.h"

QueryWorker::QueryWorker(QString &query, QString &argument, QObject *parent) :
    QThread(parent)
{
    url = new QUrl(query + argument);
    reply = NULL;
}

QueryWorker::~QueryWorker()
{
}

void QueryWorker::run()
{
    QEventLoop *looper = new QEventLoop(this);
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);

    reply = qnam->get(QNetworkRequest(*url));
    connect(reply, SIGNAL(finished()), looper, SLOT(quit()));
    looper->exec();

    QXmlStreamReader reader(reply->readAll());

    QStringList * results = new QStringList();
    QString data;
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.name() == "suggestion") {
            data = reader.attributes().value("data").toString();
            if (!data.isNull() && !data.isEmpty()) {
                results->append(data + ' ');
            }
        }
    }

    delete looper;
    delete reply;
    delete qnam;
    delete url;

    emit queryFinished(results);
    terminate();
}

void QueryWorker::abort()
{
    if (reply != NULL) {
        reply->abort();
        delete reply;
    }

    delete url;

    terminate();
}

#ifndef CONTAINSCOMPLETER_H
#define CONTAINSCOMPLETER_H

#include <QCompleter>
#include <QStringListModel>

class ContainsCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit ContainsCompleter(const QStringList &words, QObject *parent = 0);
    explicit ContainsCompleter(QStringList *words, QObject *parent = 0);

    inline void update(QString word);
    inline QString word();

private:
    QStringList m_list;
    QStringListModel m_model;
    QString m_word;

};

#endif // CONTAINSCOMPLETER_H

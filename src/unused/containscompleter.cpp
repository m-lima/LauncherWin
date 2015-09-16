#include "containscompleter.h"

ContainsCompleter::ContainsCompleter(const QStringList& words, QObject *parent) :
    QCompleter(parent), m_list(words), m_model()
{
    setModel(&m_model);
}

ContainsCompleter::ContainsCompleter(QStringList *words, QObject *parent) :
    QCompleter(parent), m_list(*words), m_model()
{
    setModel(&m_model);
}

void ContainsCompleter::update(QString word)
{
    QRegExp expression = QRegExp(".*" + word + ".*", Qt::CaseInsensitive);
    QStringList filtered = m_list.filter(expression);
    m_model.setStringList(filtered);
    m_word = word;
    complete();
}

QString ContainsCompleter::word()
{
    return m_word;
}


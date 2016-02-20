#include "persistencehandler.h"

#include <QStandardPaths>
#include <QFile>
#include <QXmlStreamReader>
#include <QErrorMessage>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include "constants.h"

void PersistenceHandler::saveHistory(QString const &target, QStringList const &historyList, QObject *parent)
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append('/');
    path.append(target);
    path.append(FILE_HISTORY_EXTENSION);
    QFile *history = new QFile(path, parent);

    if (history->open(QIODevice::WriteOnly)) {
        QTextStream stream(history);

        QStringListIterator argumentIterator(historyList);
        while (argumentIterator.hasNext()) {
            stream << argumentIterator.next() << "\n";
        }

        history->close();
    }

    delete history;
}

void PersistenceHandler::loadHistory(QString const &target, QStringList *list, QObject *parent)
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append('/');
    path.append(target);
    path.append(FILE_HISTORY_EXTENSION);
    QFile *history = new QFile(path, parent);

    if (history->open(QIODevice::ReadOnly)) {
        QTextStream stream(history);
        QString line;

        while (!stream.atEnd()) {
            line = stream.readLine().trimmed();

            if (line.isEmpty()) {
                continue;
            }

            list->append(line);
        }

        history->close();
    }

    delete history;
}

void PersistenceHandler::loadLast(QString *target, QString *argument, QObject *parent)
{
    target->clear();
    argument->clear();

    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append(FILE_LAST);
    QFile *last = new QFile(path, parent);

    if (last->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader reader(last);

        while(!reader.atEnd()) {
            reader.readNextStartElement();

            if (reader.isEndElement()) {
                continue;
            }

            if (reader.name() == XML_TARGET) {
                target->append(reader.readElementText());
            } else if (reader.name() == XML_ARGUMENT) {
                argument->append(reader.readElementText());
            }
        }

        last->close();
    }

    delete last;
}

void PersistenceHandler::saveLast(QString const &target, QString const &argument, QObject *parent)
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append(FILE_LAST);
    QFile *last = new QFile(path, parent);

    if (last->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter writer(last);
        writer.writeStartDocument();
        writer.writeStartElement(XML_LAST);
        writer.writeTextElement(XML_TARGET, target);
        writer.writeTextElement(XML_ARGUMENT, argument);
        writer.writeEndElement();
        writer.writeEndDocument();
        last->close();
    }

    delete last;
}

QList<Target *> *PersistenceHandler::loadTargets(bool fetchDisabled, QObject *parent)
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append(FILE_TARGETS);
    QFile *config = new QFile(path, parent);

//    QErrorMessage errorMessage;

    QList<Target *> *targets = new QList<Target *>();

    if (config->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader reader(config);
        QXmlStreamAttributes attributes;

        QString hotkey;
        QString variableString;

        Target *target;

        while(!reader.atEnd()) {
            reader.readNextStartElement();

            if (reader.name() == XML_MAIN) {
                continue;
            }

            if (reader.name() == XML_TARGET) {
                if (reader.isEndElement()) {
                    //Incomplete target. Should be ignored
                    continue;
                }

                target = new Target();
                attributes = reader.attributes();

                if (attributes.size() != 1) {
//                    errorMessage.showMessage("Wrong number of attibutes", EDIT_ERROR_TYPE_WRONG_ATT_NUMBER);
//                    errorMessage.exec();
                    continue;
                }

                variableString = reader.attributes().at(0).value().toString();
                if (variableString.isEmpty()) {
                    continue;
                }

                target->setName(variableString);

                do {
                    reader.readNextStartElement();
                    if (reader.isEndElement()) {
                        continue;
                    }

                    variableString = reader.name().toString();

                    if (variableString == XML_ENABLED) {
                        target->setEnabled(reader.readElementText() == "true");
                        if (!fetchDisabled && !target->isEnabled()) {
                            break;
                        }
                    } else if (variableString == XML_COMMAND) {
                        target->setCommand(reader.readElementText());
                    } else if (variableString == XML_QUERY) {
                        target->setQuery(reader.readElementText());
                    } else if (variableString == XML_HOTKEY) {
                        attributes = reader.attributes();
                        if (attributes.size() != 1) {
//                            errorMessage.showMessage("Wrong number of attibutes", EDIT_ERROR_TYPE_WRONG_ATT_NUMBER);
//                            errorMessage.exec();
                            continue;
                        }

                        hotkey = attributes.at(0).value().toString();

                        do {
                            reader.readNextStartElement();
                            if (reader.isEndElement()) {
                                continue;
                            }

                            variableString = reader.name().toString();

                            if (variableString == XML_MOD) {
                                hotkey.insert(0, reader.readElementText() + XML_MOD_DIVIDER);
                            }

                        } while (reader.name() != XML_HOTKEY);

                        target->setHotKey(hotkey);
                    }
                } while (reader.name() != XML_TARGET);

                if (!target->getName().isEmpty() && (fetchDisabled || target->isEnabled())) {
                    targets->append(target);
                }
            }
        }

        config->close();
    }

    delete config;

    return targets;
}

void PersistenceHandler::saveTargets(QList<Target *> *targets, QObject *parent)
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    path.append(FILE_TARGETS);
    QFile *config = new QFile(path, parent);

    if (config->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter writer(config);
        writer.setAutoFormatting(true);
        writer.setAutoFormattingIndent(-1);
        writer.writeStartDocument();
        writer.writeStartElement(XML_MAIN);

        QStringList split;
        QString upper;

        QList<Target *>::const_iterator target;
        for (target = targets->cbegin(); target != targets->cend(); ++target) {
            writer.writeStartElement(XML_TARGET);
                writer.writeAttribute(XML_NAME, (*target)->getName());
                writer.writeTextElement(XML_ENABLED, (*target)->isEnabled() ? "true" : "false");
                writer.writeTextElement(XML_COMMAND, (*target)->getCommand());
                writer.writeTextElement(XML_QUERY, (*target)->getQuery());
                writer.writeStartElement(XML_HOTKEY);
                if ((*target)->getHotKey().isEmpty()) {
                    writer.writeTextElement(XML_KEY_ATTRIBUTE, "");
                } else {
                    split = (*target)->getHotKey().split(XML_MOD_DIVIDER);

                    QStringListIterator splitElement(split);
                    splitElement.toBack();
                    while (splitElement.hasPrevious()) {
                        upper = splitElement.previous().toUpper();
                        if (upper.size() == 1) {
                            writer.writeAttribute(XML_KEY_ATTRIBUTE, upper);
                        } else {
                            if (upper == HOT_SHIFT) {
                                writer.writeTextElement(XML_MOD, HOT_SHIFT);
                            } else if (upper == HOT_CTRL) {
                                writer.writeTextElement(XML_MOD, HOT_CTRL);
                            } else if (upper == HOT_ALT) {
                                writer.writeTextElement(XML_MOD, HOT_ALT);
                            }
                        }
                    }
                }
                writer.writeEndElement();
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
    }

    delete config;
}

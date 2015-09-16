#ifndef TARGET_H
#define TARGET_H

#include <QString>
#include <QListWidgetItem>

class Target : public QListWidgetItem
{
    Q_OBJECT
public:
    explicit Target(QString, QString, QString, char, bool);
    ~Target();
    const QString & getTarget();
    const QString & getCommand();
    const QString & getSuggestion();
    const char & getHotkey();
    const bool & isEnabled();

private:
    QString target;
    QString command;
    QString suggestion;
    char hotKey;
    bool enabled;

};

#endif // TARGET_H

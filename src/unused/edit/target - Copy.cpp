#include "target.h"

Target::Target(QString target, QString command, QString suggestion, char hotKey, bool enabled) :
    QString(target)
{
    this->target = target;
    this->command = command;
    this->suggestion = suggestion;
    this->hotKey = hotKey;
    this->enabled = enabled;
}

Target::~Target()
{
}

const QString &Target::getTarget()
{
    return target;
}

const QString &Target::getCommand()
{
    return command;
}

const QString &Target::getSuggestion()
{
    return suggestion;
}

const char &Target::getHotkey()
{
    return hotKey;
}

const bool &Target::isEnabled()
{
    return enabled;
}


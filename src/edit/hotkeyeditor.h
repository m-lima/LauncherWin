#ifndef HOTKEYEDITOR_H
#define HOTKEYEDITOR_H

#include <QLineEdit>
#include <QKeyEvent>



#include <QDebug>



#include "../util/constants.h"

class HotKeyEditor : public QLineEdit
{
    Q_OBJECT
public:
    explicit HotKeyEditor(QWidget *parent = 0);

private:
    virtual void keyReleaseEvent(QKeyEvent *) Q_DECL_OVERRIDE;
};

#endif // HOTKEYEDITOR_H

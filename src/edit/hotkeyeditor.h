#ifndef HOTKEYEDITOR_H
#define HOTKEYEDITOR_H

#include <QLineEdit>
#include <QKeyEvent>

class HotKeyEditor : public QLineEdit
{
    Q_OBJECT
public:
    explicit HotKeyEditor(QWidget *parent = 0);

private:
    virtual void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;
};

#endif // HOTKEYEDITOR_H

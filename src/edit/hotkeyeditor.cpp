#include "hotkeyeditor.h"

HotKeyEditor::HotKeyEditor(QWidget *parent) :
    QLineEdit(parent)
{
}

void HotKeyEditor::keyReleaseEvent(QKeyEvent *e)
{
    QLineEdit::keyReleaseEvent(e);
    char keyCode = e->key();
    QKeySequence sequence(keyCode);
    qDebug() << sequence.toString(QKeySequence::NativeText);
    if (keyCode >= 32 && keyCode <= 126) {
        QString hotKey = QString(keyCode);
        if (e->modifiers().testFlag(Qt::AltModifier)) {
            hotKey.insert(0, XML_MOD_DIVIDER);
            hotKey.insert(0, HOT_ALT);
        }
        if (e->modifiers().testFlag(Qt::ControlModifier)) {
            hotKey.insert(0, XML_MOD_DIVIDER);
            hotKey.insert(0, HOT_CTRL);
        }
        if (e->modifiers().testFlag(Qt::ShiftModifier)) {
            hotKey.insert(0, XML_MOD_DIVIDER);
            hotKey.insert(0, HOT_SHIFT);
        }
        setText(hotKey);
    }
}


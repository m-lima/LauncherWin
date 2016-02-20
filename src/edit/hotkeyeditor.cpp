#include "hotkeyeditor.h"

#include "../util/constants.h"

#include <QDebug>
//#include <QKey>

HotKeyEditor::HotKeyEditor(QWidget *parent) :
    QLineEdit(parent)
{
}

void HotKeyEditor::keyPressEvent(QKeyEvent *e)
{
    QLineEdit::keyPressEvent(e);
    char keyCode = e->key();
    QKeySequence sequence(keyCode);
    //q/Debug() << sequence.toString(QKeySequence::NativeText);
    if (keyCode >= 32 && keyCode <= 126 && e->nativeVirtualKey() > 20) {
        QString hotKey = QString(keyCode);
        qDebug() << keyCode << " (" << (int)keyCode << ")";
        qDebug() << e->nativeVirtualKey() << " (" << (int)e->nativeVirtualKey() << ")";
        qDebug() << e->nativeScanCode() << " (" << (int)e->nativeScanCode() << ")\n";
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


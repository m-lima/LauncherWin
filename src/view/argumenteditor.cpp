#include "argumenteditor.h"

ArgumentEditor::ArgumentEditor(QWidget *parent) :
    QLineEdit(parent)
{
}

void ArgumentEditor::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit(focussed());
}

void ArgumentEditor::keyReleaseEvent(QKeyEvent *e)
{
    QLineEdit::keyReleaseEvent(e);
    if (e->key() == Qt::Key_Down) {
        emit(downReleased());
    }
}

#include "argumenteditor.h"

ArgumentEditor::ArgumentEditor(QWidget *parent) :
    QLineEdit(parent)
{
}

QString ArgumentEditor::encodedText()
{
    QString original = text().trimmed();
    QString encodedString;
    for (QString::const_iterator j = original.cbegin(); j != original.cend(); j++) {
        if (j->isLetterOrNumber()) {
            encodedString.append(*j);
        } else {
            encodedString.append('%');
            encodedString.append(QString::number(j->unicode(), 16));
        }
    }

    return encodedString;
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

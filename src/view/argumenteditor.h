#ifndef ARGUMENTEDITOR_H
#define ARGUMENTEDITOR_H

#include <QLineEdit>
#include <QKeyEvent>

class ArgumentEditor : public QLineEdit
{
    Q_OBJECT
public:
    explicit ArgumentEditor(QWidget *parent = 0);
    QString encodedText();

signals:
    void focussed();
    void downReleased();

protected:
    virtual void focusInEvent(QFocusEvent *) Q_DECL_OVERRIDE;
    virtual void keyReleaseEvent(QKeyEvent *) Q_DECL_OVERRIDE;

};

#endif // ARGUMENTEDITOR_H

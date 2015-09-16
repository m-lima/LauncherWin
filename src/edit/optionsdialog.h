#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QLocalServer>
#include <QLocalSocket>
#include "windows.h"

#include "../util/target.h"
#include "../util/constants.h"
#include "../util/persistencehandler.h"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(QList<Target *> *targets, QWidget *parent = 0);
    ~OptionsDialog();

private:
    void initialize(QList<Target *> *targets);

    Ui::OptionsDialog *ui;

    QLocalServer *server;

private slots:
    void on_lstTargets_itemSelectionChanged();
    void on_btnSave_clicked();
    void on_txtTarget_editingFinished();
    void on_txtCommand_editingFinished();
    void on_txtQuery_editingFinished();
    void on_txtHotKey_editingFinished();
    void on_chkEnabled_stateChanged(int state);
    void newConnection();
};

#endif // OPTIONSDIALOG_H

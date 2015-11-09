#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QLocalServer>

#include "../util/target.h"

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
    Ui::OptionsDialog *ui;
    QLocalServer *server;

    void initialize(QList<Target *> *targets);

private slots:
    void newConnection();

    void on_lstTargets_itemSelectionChanged();
    void on_btnSave_clicked();
    void on_txtTarget_editingFinished();
    void on_txtCommand_editingFinished();
    void on_txtQuery_editingFinished();
    void on_txtHotKey_editingFinished();
    void on_chkEnabled_stateChanged(int state);
    void on_rdoQuery_toggled(bool checked);
};

#endif // OPTIONSDIALOG_H

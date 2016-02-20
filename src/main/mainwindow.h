#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalServer>

#include "../util/target.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QList<Target *> *targetList, QString target);
    ~MainWindow();

signals:
    void cancelQuery();

protected:
    void keyReleaseEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);
//    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QList<Target *> *targetList_;
    QStringList *historyList;

    QLocalServer *server;

    QString lastTarget;
    QString queryURL;

    bool googleEnabled;
    int editingCompleter;

    void execute();
    void checkTarget(QString const &target);
    void saveHistory(Target const &target);
    void updateTargetCompleter();
    void updateArgumentCompleter(QStringList *list, bool google = false);
    void initialize(QString const &target);
    void forceFocus();

private slots:
    void newConnection();
    void queryDone(QStringList *);

    void on_txtArgument_focussed();
    void on_txtArgument_returnPressed();
    void on_txtArgument_downReleased();
    void on_txtArgument_textEdited();
    void on_txtTarget_returnPressed();
    void on_txtTarget_textChanged(QString);
};

#endif // MAINWINDOW_H

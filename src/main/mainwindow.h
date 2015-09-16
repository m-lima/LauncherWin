#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QKeyEvent>
#include <QCompleter>
#include <QProcess>
#include <QDesktopServices>
#include <QTextStream>
#include <QLocalServer>
#include <QLocalSocket>
#include <QStringListModel>

#include "queryworker.h"
#include "googleresultdelegate.h"
#include "../util/constants.h"
#include "../util/persistencehandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QList<Target *> *targets, QString target);
    ~MainWindow();

signals:
    void cancelQuery();

protected:
    void keyReleaseEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);
//    void closeEvent(QCloseEvent *);

private:
    void execute();
    void checkTarget(const QString & target);
    void saveHistory(const Target &target);
    void updateTargetCompleter();
    void updateArgumentCompleter(QStringList * list, bool google = false);
    void initialize(const QString & target);

    Ui::MainWindow *ui;
    QList<Target*> *targetList;
    QStringList *historyList;

    QLocalServer *server;

    QString lastTarget;
    QString queryURL;

    bool googleEnabled;

private slots:
    void on_txtArgument_focussed();
    void on_txtArgument_returnPressed();
    void on_txtArgument_downReleased();
    void on_txtArgument_textEdited(QString);
    void on_txtTarget_returnPressed();
    void on_txtTarget_textChanged(QString);
    void newConnection();
    void queryDone(QStringList *);
};

#endif // MAINWINDOW_H

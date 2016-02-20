#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QIcon const &icon, QObject *parent);
    ~TrayIcon();

private:
    QMenu *menu;

signals:
    void open();
    void close();
    void edit();

private slots:
    void clicked(QSystemTrayIcon::ActivationReason);
    void onOpenClicked();
    void onCloseClicked();
    void onEditClicked();

};

#endif // TRAYICON_H

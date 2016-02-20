#include "trayicon.h"

TrayIcon::TrayIcon(QIcon const &icon, QObject *parent) :
    QSystemTrayIcon(icon, parent)
{

    menu = new QMenu();
    menu->addAction("Open", this, SLOT(onOpenClicked()));
    menu->addAction("Edit", this, SLOT(onEditClicked()));
    menu->addSeparator();
    menu->addAction("Exit", this, SLOT(onCloseClicked()));

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(clicked(QSystemTrayIcon::ActivationReason)));
}

TrayIcon::~TrayIcon()
{
    delete menu;
}

void TrayIcon::onCloseClicked()
{
    emit close();
}

void TrayIcon::onOpenClicked()
{
    emit open();
}

void TrayIcon::onEditClicked()
{
    emit edit();
}

void TrayIcon::clicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context) {
        menu->popup(QCursor::pos());
    }
}

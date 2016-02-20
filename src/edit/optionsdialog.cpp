#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QLocalSocket>

#include "../util/constants.h"
#include "../util/persistencehandler.h"

OptionsDialog::OptionsDialog(QList<Target *> *targets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    server = new QLocalServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    server->listen(SERVER_EDIT);

    initialize(targets);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
    server->close();
    delete server;
}

void OptionsDialog::newConnection()
{
    QLocalSocket *socket = server->nextPendingConnection();

    socket->close();
    delete socket;

    showNormal();
    activateWindow();
}

void OptionsDialog::initialize(QList<Target *> *targets)
{
    QList<Target *>::const_iterator i;
    for (i = targets->cbegin(); i != targets->cend(); ++i) {
        ui->lstTargets->addItem(*i);
    }

    if (ui->lstTargets->count() > 0) {
        ui->lstTargets->setFocus();
        ui->lstTargets->setCurrentRow(0);
    }
}

//////////////////////////////////
////       GENERATE XML       ////
//////////////////////////////////

//void OptionsDialog::initialize()
//{
////    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
////    path.append("/targets.cfg");
////    QFile *config = new QFile(path, this);

//    QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
//    QFile *config = new QFile(path + "/targets.cfg", this);
//    QFile *out = new QFile(path + "/targetss.xml", this);

//    if (config->open(QIODevice::ReadOnly)) {
//        Target *target;
//        bool enabled;
//        QBrush disabledPaint(QColor(150, 150, 150));

//        if (out->open(QIODevice::WriteOnly)) {

//            QTextStream stream(config);
//            QString line;
//            QStringList split;
//            QXmlStreamWriter writer(out);
//            writer.setAutoFormatting(true);
//            writer.setAutoFormattingIndent(-1);
//            writer.writeStartDocument();
//            writer.writeStartElement("targets");

//            while(!stream.atEnd()) {
//                target = new Target(ui->lstTargets);
//                line = stream.readLine().trimmed();

//                enabled = !line.startsWith("#");
//                target->setEnabled(enabled);
//    //            if (!enabled) {
//    //                target->setData(Qt::ForegroundRole, 0);//disabledPaint);
//    //            }

//                split = line.split(';');

//                //target = split.at(0).trimmed().remove(0, enabled);
//                //item->setData(Qt::DisplayRole, split.at(0).trimmed().remove(0, !enabled));
//                target->setName(split.at(0).trimmed().remove(0, !enabled));

//                if (split.size() > 1) {
//                    //command = split.at(1).trimmed();
//                    //item->setData(COMMAND, split.at(1).trimmed());
//                    target->setCommand(split.at(1).trimmed());
//                } else {
//                    //command = "";
//                    //item->setData(COMMAND, "");
//                    target->setCommand();
//                }

//                if (split.size() > 2) {
//                    //hotKey = split.at(2).trimmed().toUInt();
//                    //item->setData(HOTKEY, split.at(2).trimmed());
//                    target->setHotKey(split.at(2).trimmed());
//                } else {
//                    //hotKey = 0;
//                    //item->setData(HOTKEY, "");
//                    target->setHotKey();
//                }

//                if (split.size() > 3) {
//                    //suggestion = split.at(3).trimmed();
//                    //item->setData(SUGGESTION, split.at(3).trimmed());
//                    target->setSuggestion(split.at(3).trimmed());
//                } else {
//                    //suggestion = "";
//                    //item->setData(SUGGESTION, "");
//                    target->setSuggestion();
//                }

//    //            if (!first) {
//    //                ui->txtTarget->setText(target);
//    //                ui->txtCommand->setText(command);
//    //                ui->chkEnabled->setChecked(enabled);
//    //                ui->txtHotKey->setText(QString(hotKey));
//    //                first = true;
//    //            }

//    //            targetItem(target, command, suggestion, hotKey, enabled);
//    //            targetList.append(Target(target, command, suggestion, hotKey, enabled));
//                ui->lstTargets->addItem(target);

//                writer.writeStartElement("target");
//                    writer.writeAttribute("name", target->getName());
//                    writer.writeTextElement("enabled", target->isEnabled() ? "true" : "false");
//                    writer.writeTextElement("command", target->getCommand());
//                    writer.writeTextElement("suggestion", target->getSuggestion());
//                    writer.writeStartElement("hotkey");
//                    writer.writeAttribute("key", target->getHotKey());
//                    if (!target->getHotKey().isEmpty()) {
//                        writer.writeTextElement("mod", "RCTRL");
//                        writer.writeTextElement("mod", "RALT");
//                    }
//                    writer.writeEndElement();
//                writer.writeEndElement();
//            }

//            writer.writeEndElement();
//            writer.writeEndDocument();
//            out->close();
//        }

//        config->close();
//    }

//    //ui->lstTargets->insertItems(0, targetList);
//    //    if (first) {
//    if (ui->lstTargets->count() > 0) {
//        ui->lstTargets->setFocus();
//        ui->lstTargets->setCurrentRow(0);
//    }

//    delete out;
//    delete config;
//}

void OptionsDialog::on_lstTargets_itemSelectionChanged()
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    ui->txtTarget->setText(target->getName());
    ui->txtCommand->setText(target->getCommand());
    ui->txtQuery->setText(target->getQuery());
    ui->chkEnabled->setChecked(target->isEnabled());
    ui->txtHotKey->setText(target->getHotKey());
}

void OptionsDialog::on_btnSave_clicked()
{
    QList<Target *> *targets = new QList<Target*>();

    for(int i = 0; i < ui->lstTargets->count(); ++i)
    {
        targets->append(static_cast<Target *>(ui->lstTargets->item(i)));
    }

    PersistenceHandler::saveTargets(targets, this);
    delete targets;

    qApp->exit(MAIN_EDIT_SAVE);
}

void OptionsDialog::on_txtTarget_editingFinished()
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    target->setName(ui->txtTarget->text());
}

void OptionsDialog::on_txtCommand_editingFinished()
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    target->setCommand(ui->txtCommand->text());
}

void OptionsDialog::on_txtQuery_editingFinished()
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    target->setQuery(ui->txtQuery->text());
}

void OptionsDialog::on_txtHotKey_editingFinished()
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    target->setHotKey(ui->txtHotKey->text());
}

void OptionsDialog::on_chkEnabled_stateChanged(int state)
{
    Target *target = static_cast<Target *>(ui->lstTargets->currentItem());
    target->setEnabled(state);
}


void OptionsDialog::on_rdoQuery_toggled(bool checked)
{
    ui->txtQuery->setEnabled(checked);
    ui->lblQuery->setEnabled(checked);
}

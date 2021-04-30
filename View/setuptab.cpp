#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"
#include <QStringListModel>

SetupTab::SetupTab(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SetupTab)
{
    ui->setupUi(this);
    ui->btnDisconnect->setEnabled(false);
    ui->gbDirectCommands->setEnabled(false);
    ui->gbInstrumentMessages->setEnabled(false);
}

SetupTab::~SetupTab()
{
    Utils::DestructorMsg(this);
    delete ui;
}

void SetupTab::SetHostName(const QString &value)
{
    ui->editIpAddress->setText(value);
    emit NotifyHostNameChanged(value);
}

void SetupTab::SetPort(quint16 value)
{
    ui->editPort->setText(QString::number(value));
    emit NotifyPortChanged(value);
}

void SetupTab::SetCommands(QStringListModel &commands)
{
    ui->cmbCommands->setModel(&commands);
}

void SetupTab::onStatusUpdated(const QString &statusMsg)
{
    ui->textInstrumentMessage->append(statusMsg);
}

void SetupTab::onConnected()
{
    ui->textInstrumentMessage->append("Connected");
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->gbDirectCommands->setEnabled(true);
    ui->gbInstrumentMessages->setEnabled(true);
}

void SetupTab::onDisconnected()
{
    ui->textInstrumentMessage->append("Disconnected");
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->gbDirectCommands->setEnabled(false);
    ui->gbInstrumentMessages->setEnabled(false);
}

void SetupTab::on_editIpAddress_editingFinished()
{
    emit NotifyHostNameChanged(ui->editIpAddress->text());
}

void SetupTab::on_editPort_editingFinished()
{
    bool ok;
    int result = ui->editPort->text().toInt(&ok);
    if (!ok) {
        ui->textInstrumentMessage->append("Invalid Port Number " + result);
    }
    else{
        emit NotifyPortChanged(result);
    }
}

void SetupTab::on_btnConnect_clicked()
{
    emit NotifyConnectClicked();
}

void SetupTab::on_btnDisconnect_clicked()
{
    emit NotifyDiconnectClicked();
}

void SetupTab::on_btnSend_clicked()
{
    emit NotifySendClicked();
}

void SetupTab::on_btnReceive_clicked()
{
    emit NotifyReceiveClicked();
}

void SetupTab::on_btnClear_clicked()
{
    ui->textInstrumentMessage->clear();
}

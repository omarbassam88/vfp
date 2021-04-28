#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"
#include <QStringListModel>

SetupTab::SetupTab(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SetupTab)
{
    ui->setupUi(this);
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

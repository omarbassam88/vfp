#ifndef SETUPTAB_H
#define SETUPTAB_H

#include <QWidget>

namespace Ui {
class SetupTab;
}

class QStringListModel;

class SetupTab : public QWidget {
  Q_OBJECT

public:
  explicit SetupTab(QWidget *parent = nullptr);
  ~SetupTab();

  void SetHostName(const QString &value);
  void SetPort(quint16 value);
  void SetCommands(QStringListModel &commands);

signals:
  void NotifyHostNameChanged(const QString &value);
  void NotifyPortChanged(quint16 value);
  void NotifyConnectClicked();
  void NotifyDiconnectClicked();
  void NotifySendClicked();
  void NotifyReceiveClicked();

public slots:
  void onStatusUpdated(const QString &statusMsg);
  void onConnected();
  void onDisconnected();

private slots:
  void on_editIpAddress_editingFinished();

  void on_editPort_editingFinished();

  void on_btnConnect_clicked();

  void on_btnDisconnect_clicked();

  void on_btnSend_clicked();

  void on_btnReceive_clicked();

  void on_btnClear_clicked();

private:
  Ui::SetupTab *ui;
};

#endif // SETUPTAB_H

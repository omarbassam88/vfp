#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>

class InstSocket;

class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent, InstSocket& socket);
    ~Instrument();

    void Connect();
    void Disconnect();
    bool isConnected() const;
    QString GetHostName() const;
    quint16 GetPort() const;
    void SetLongWaitMs(int value);
    void SetShortWaitMs(int value);

signals:
    void NotifyConnected();
    void NotifyDisconnected();
    void NotifyDateSent(const QString& dataSent);
    void NotiftDataReceived(const QString& readData);
    void NotifyErrorDetected(const QString& errorMsg);
    void NotifyStatusUpdated(const QString& statusMsg);

public slots:
    void onConnected();
    void onDisconnected();
    void onHostNameChanged(const QString& hostName);
    void onPortChanged(quint16 port);
    void onSendRequest(const QString& dataToSend);
    void onReceiveRequest();

private:
    InstSocket& m_socket;
    QString m_lastCommandSent;

    void WireConnections();
};

#endif // INSTRUMENT_H

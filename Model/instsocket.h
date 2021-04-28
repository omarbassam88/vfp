#ifndef INSTSOCKET_H
#define INSTSOCKET_H

#include <QObject>

class QTcpSocket;

class InstSocket : public QObject
{
    Q_OBJECT
public:
    explicit InstSocket(QObject *parent = nullptr);
    ~InstSocket();
    bool Connect();
    bool IsOpen();
    void Disconnect();

    QString GetHostName() const { return m_hostName; };
    void SetHostName(const QString& value);
    quint16 GetPort() { return m_port; };
    void SetPort(quint16 value);
    void SetLongWaitMs(int value) { m_longWaitMs = value;};
    void SetShortWaitMs(int value) { m_shortWaitMs = value; };
    QString ReadData() const;
    void WriteData(const QString& data) const;

signals:
    void NotifyConnected();
    void NotifyDisconnected();

private slots:
    void onConnected();
    void onDisconnected();
private:
    QTcpSocket& m_socket;
    QString m_hostName;
    quint16 m_port;
    int m_longWaitMs;
    int m_shortWaitMs;

};

#endif // INSTSOCKET_H

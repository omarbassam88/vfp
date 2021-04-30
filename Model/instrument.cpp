#include "instrument.h"
#include "instsocket.h"
#include "utils.h"
#include <QDebug>
#include "provider.h"
#include "settings.h"

Instrument::Instrument(QObject *parent, InstSocket& socket)
    : QObject(parent)
    , m_socket(socket)
    , m_lastCommandSent("")
{

    WireConnections();
}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}

void Instrument::Connect()
{
    Disconnect();
    bool connected = m_socket.Connect();
    if (!connected) {
        emit NotifyErrorDetected(tr("Cannot Connect to Instrument"));
    }

}

void Instrument::Disconnect()
{
    if (m_socket.IsOpen()) {
        m_socket.Disconnect();

    }

}

bool Instrument::isConnected() const
{
    return m_socket.IsOpen();
}

QString Instrument::GetHostName() const
{
    return m_socket.GetHostName();
}

quint16 Instrument::GetPort() const
{
    return  m_socket.GetPort();
}

void Instrument::SetLongWaitMs(int value)
{
    m_socket.SetLongWaitMs(value);

}

void Instrument::SetShortWaitMs(int value)
{
    m_socket.SetShortWaitMs(value);
}


void Instrument::WireConnections()
{
    connect(&m_socket, &InstSocket::NotifyConnected, this, &Instrument::onConnected);
    connect(&m_socket, &InstSocket::NotifyDisconnected, this, &Instrument::onDisconnected);
}

void Instrument::onConnected()
{
    emit NotifyConnected();
}

void Instrument::onDisconnected()
{
    emit NotifyDisconnected();
    qDebug() << "Disconnected";
}

void Instrument::onHostNameChanged(const QString &hostName)
{
    m_socket.SetHostName(hostName);
}

void Instrument::onPortChanged(quint16 port)
{
    m_socket.SetPort(port);
}

void Instrument::onSendRequest(const QString &dataToSend)
{
    m_lastCommandSent = dataToSend;
    qDebug() << "Instrument read to send data " << dataToSend;
    m_socket.WriteData(dataToSend);
    emit NotifyDateSent(dataToSend);
}

void Instrument::onReceiveRequest()
{
    QString input_buffer = m_socket.ReadData();
    if (input_buffer.size() == 0) {
        emit NotiftDataReceived("No Data Received.");
    }
    else{
        emit NotiftDataReceived(input_buffer);
    }

}

void Instrument::onPulseWidthChanged(double value)
{
    Settings& settings = Provider::GetSettingsInstance();
    auto pw_cmd = settings.GetPwCommand() + "%1";
    auto full_cmd = pw_cmd.arg(value);
    m_socket.WriteData(full_cmd);
    emit NotifyStatusUpdated(full_cmd);

}

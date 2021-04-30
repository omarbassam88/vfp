#ifndef CONTROLVIEWMANAGER_H
#define CONTROLVIEWMANAGER_H

#include <QObject>

class ControlTab;
class Instrument;

class ControlViewManager : public QObject
{
    Q_OBJECT
public:
    explicit ControlViewManager(QObject *parent, ControlTab& controlTab, Instrument& instrument);
    ~ControlViewManager();

signals:
    void NotifyConnected();

public slots:
    void onConnected();
    void onDisconnected();

private:
    ControlTab& m_controlTab;
    Instrument& m_instrument;

    void WireControls();
    void WireConnected();
};

#endif // CONTROLVIEWMANAGER_H

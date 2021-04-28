#ifndef SETUPVIEWMANAGER_H
#define SETUPVIEWMANAGER_H

#include <QObject>

class SetupTab;
class Instrument;
class Settings;

class SetupViewManager : public QObject
{
    Q_OBJECT
public:
    explicit SetupViewManager(QObject *parent, SetupTab& tab, Instrument& inst, Settings& config );
    ~SetupViewManager();

signals:
    void NotifyStatusUpdated(const QString& value);

private:
    SetupTab& m_setupTab;
    Instrument& m_instrument;

    void WireSettings(Settings& config);
    void WireHostAndPort();
    void WireMessages();
};

#endif // SETUPVIEWMANAGER_H

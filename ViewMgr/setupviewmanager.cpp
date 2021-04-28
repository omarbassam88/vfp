#include "setupviewmanager.h"
#include "Model/instrument.h"
#include "Model/settings.h"
#include "View/setuptab.h"
#include "utils.h"

SetupViewManager::SetupViewManager(QObject *parent, SetupTab &tab, Instrument &inst, Settings &config)
    : QObject(parent)
    , m_setupTab(tab)
    , m_instrument(inst)
{
    WireSettings(config);
    config.ParseJsonData();
    WireHostAndPort();
    WireMessages();

    m_setupTab.SetHostName(config.GetHostName());
    m_setupTab.SetPort(config.GetPortNumber());
    m_setupTab.SetCommands(config.GetCommands());
    auto long_ms = config.GetLongWaitMs();
    auto short_ms = config.GetShortWaitMs();
    m_instrument.SetLongWaitMs(long_ms);
    m_instrument.SetShortWaitMs(short_ms);

    emit NotifyStatusUpdated(tr("Long Wait %1").arg(long_ms));
    emit NotifyStatusUpdated(tr("ٍShort Wait %1").arg(short_ms));


}

SetupViewManager::~SetupViewManager()
{
    Utils::DestructorMsg(this);
}

void SetupViewManager::WireSettings(Settings &config)
{
    connect(&config , &Settings::NotifyStatusMessage, &m_setupTab, &SetupTab::onStatusUpdated);
}

void SetupViewManager::WireHostAndPort()
{
    connect(&m_setupTab, &SetupTab::NotifyHostNameChanged, &m_instrument, &Instrument::onHostNameChanged);
    connect(&m_setupTab, &SetupTab::NotifyPortChanged, &m_instrument, &Instrument::onPortChanged);
}

void SetupViewManager::WireMessages()
{
    connect(&m_instrument, &Instrument::NotifyErrorDetected, &m_setupTab, &SetupTab::onStatusUpdated);
    connect(&m_instrument, &Instrument::NotifyStatusUpdated, &m_setupTab, &SetupTab::onStatusUpdated);
    connect(this, &SetupViewManager::NotifyStatusUpdated, &m_setupTab, &SetupTab::onStatusUpdated);
}

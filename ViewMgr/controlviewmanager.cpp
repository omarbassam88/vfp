#include "controlviewmanager.h"
#include "View/controltab.h"
#include "Model/instrument.h"
#include "Model/settings.h"
#include "utils.h"

ControlViewManager::ControlViewManager(QObject *parent, ControlTab &controlTab, Instrument &instrument)
    : QObject(parent)
    , m_controlTab(controlTab)
    , m_instrument(instrument)
{
    WireControls();
    WireConnected();
    m_controlTab.setEnabled(false);
}

ControlViewManager::~ControlViewManager()
{
    Utils::DestructorMsg(this);
}

void ControlViewManager::onConnected()
{
    m_controlTab.setEnabled(true);
}

void ControlViewManager::onDisconnected()
{
    m_controlTab.setEnabled(false);

}

void ControlViewManager::WireControls()
{
    connect(&m_controlTab, &ControlTab::NotifyPulseWidthChanged, &m_instrument, &Instrument::onPulseWidthChanged);
}

void ControlViewManager::WireConnected()
{
    connect(&m_instrument, &Instrument::NotifyConnected, this, &ControlViewManager::onConnected);
    connect(&m_instrument, &Instrument::NotifyDisconnected, this, &ControlViewManager::onDisconnected);
}

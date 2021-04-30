#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "utils.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instrument.h"
#include "Model/instsocket.h"
#include "ViewMgr/setupviewmanager.h"
#include "ViewMgr/controlviewmanager.h"

StartUp::StartUp()
  : QObject(nullptr)
  , m_setupTab(*new SetupTab(nullptr))
  , m_controlTab(*new ControlTab(nullptr))
  , m_mainView(*new MainView(nullptr, m_setupTab, m_controlTab))
  , m_instrument(new Instrument(this, *new InstSocket(this)))
  , m_setupVm(new SetupViewManager(this, m_setupTab, *m_instrument, Provider::GetSettingsInstance()))
  , m_controlVm(new ControlViewManager(this, m_controlTab, *m_instrument))
{

}

StartUp::~StartUp()
{
  Utils::DestructorMsg(this);
  delete &m_mainView;
}

void
StartUp::show() const
{
  m_mainView.show();
}

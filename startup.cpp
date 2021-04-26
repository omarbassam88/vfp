#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "utils.h"

StartUp::StartUp()
  : QObject(nullptr)
  , m_setupTab(*new SetupTab(nullptr))
  , m_mainView(*new MainView(nullptr, m_setupTab))
{}

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

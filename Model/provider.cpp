#include "provider.h"
#include "Model/settings.h"
#include <QString>

static QString SETTINGS_FILE = QStringLiteral("settings.json");
std::unique_ptr<Settings> Provider::m_settingsInstance = nullptr;

Provider::Provider()
{

}

Settings &Provider::GetSettingsInstance()
{
    if(m_settingsInstance == nullptr)
    {
        m_settingsInstance = std::make_unique<Settings>(nullptr, SETTINGS_FILE);
    }

    return *m_settingsInstance;
}

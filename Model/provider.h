#ifndef PROVIDER_H
#define PROVIDER_H

#include <memory>
class Settings;

class Provider final {
public:
  Provider();
  static Settings &GetSettingsInstance();

private:
  static std::unique_ptr<Settings> m_settingsInstance;
};

#endif // PROVIDER_H

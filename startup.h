#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

class MainView;
class SetupTab;
class Instrument;
class SetupViewManager;
class ControlTab;
class ControlViewManager;

class StartUp final : public QObject {
  Q_OBJECT
public:
  explicit StartUp();
  ~StartUp();
  void show() const;

public slots:
private:
  SetupTab &m_setupTab;
  ControlTab &m_controlTab;
  MainView &m_mainView;
  Instrument *m_instrument;
  SetupViewManager *m_setupVm;
  ControlViewManager *m_controlVm;

signals:
};

#endif // STARTUP_H

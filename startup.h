#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

class MainView;
class SetupTab;

class StartUp final : public QObject
{
    Q_OBJECT
public:
    explicit StartUp();
    ~StartUp();
    void show() const;

public slots:
private:
    SetupTab& m_setupTab;
    MainView& m_mainView;

signals:

};

#endif // STARTUP_H

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainView;
}
QT_END_NAMESPACE

class SetupTab;
class ControlTab;

class MainView : public QMainWindow
{
  Q_OBJECT

public:
  MainView(QWidget* parent, SetupTab& setupTab, ControlTab &controlTab);
  ~MainView();

private:
  Ui::MainView* ui;
};
#endif // MAINVIEW_H

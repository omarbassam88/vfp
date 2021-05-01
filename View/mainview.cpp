#include "mainview.h"
#include "./ui_mainview.h"
#include "View/aboutbox.h"
#include "controltab.h"
#include "setuptab.h"

MainView::MainView(QWidget *parent, SetupTab &setupTab, ControlTab &controlTab)
    : QMainWindow(parent), ui(new Ui::MainView) {
  ui->setupUi(this);
  setupTab.setParent(this);
  controlTab.setParent(this);
  ui->loSetupTab->addWidget(&setupTab);
  ui->loControlTab->addWidget(&controlTab);
}

MainView::~MainView() { delete ui; }

void MainView::on_action_About_triggered() {
  AboutBox aboutBox;
  aboutBox.show();
  aboutBox.exec();
}

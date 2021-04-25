#include "mainview.h"
#include "./ui_mainview.h"
#include "setuptab.h"

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
{
    ui->setupUi(this);
    auto setupTab = new SetupTab(this);
    ui->loSetupTab->addWidget(setupTab);
}

MainView::~MainView()
{
    delete ui;
}


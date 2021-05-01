#include "controltab.h"
#include "ui_controltab.h"
#include "utils.h"

ControlTab::ControlTab(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlTab) {
  ui->setupUi(this);
}

ControlTab::~ControlTab() {
  Utils::DestructorMsg(this);
  delete ui;
}

void ControlTab::on_spnWidth_valueChanged(double value) {
  emit NotifyPulseWidthChanged(value);
}

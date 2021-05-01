#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>

namespace Ui {
class ControlTab;
}

class ControlTab : public QWidget {
  Q_OBJECT

public:
  explicit ControlTab(QWidget *parent = nullptr);
  ~ControlTab();

signals:
  void NotifyPulseWidthChanged(double value);

private slots:
  void on_spnWidth_valueChanged(double value);

private:
  Ui::ControlTab *ui;
};

#endif // CONTROLTAB_H

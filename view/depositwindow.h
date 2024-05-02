#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DepositWindow;
}
QT_END_NAMESPACE

class DepositWindow : public QMainWindow {
  Q_OBJECT

 public:
  DepositWindow(my::Controller contr, QWidget *parent = nullptr);
  ~DepositWindow();

  void reset_window();

 private slots:
  void on_pushButton_reset_clicked();

  void on_pushButton_calculate_clicked();

 private:
  Ui::DepositWindow *ui;

  my::Controller controller;
};
#endif  // DEPOSITWINDOW_H

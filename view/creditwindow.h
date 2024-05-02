#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditWindow;
}
QT_END_NAMESPACE

class CreditWindow : public QMainWindow {
  Q_OBJECT

 public:
  CreditWindow(my::Controller contr, QWidget *parent = nullptr);
  ~CreditWindow();

  void reset_window();

 private slots:
  void on_comboBox_type_currentIndexChanged();
  void on_pushButton_reset_clicked();
  void on_pushButton_calculate_clicked();

 private:
  Ui::CreditWindow *ui;

  my::Controller controller;
};
#endif  // CREDITWINDOW_H

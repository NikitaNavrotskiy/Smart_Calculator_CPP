#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../controller/controller.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "smartgraph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcWindow;
}
QT_END_NAMESPACE

class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  CalcWindow(my::Controller contr, QWidget *parent = nullptr);
  ~CalcWindow();

 private slots:
  void on_pushButton_clearall_clicked();

  void on_pushButton_openbrace_clicked();

  void on_pushButton_closebrace_clicked();

  void on_pushButton_pow_clicked();

  void on_pushButton_delete_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_div_clicked();

  void on_pushButton_mod_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_mul_clicked();

  void on_pushButton_equal_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_sub_clicked();

  void on_pushButton_0_clicked();

  void on_pushButton_dot_clicked();

  void on_pushButton_add_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_asin_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_atan_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_ln_clicked();

  void on_pushButton_credit_clicked();

  void on_pushButton_deposit_clicked();

  void on_pushButton_x_clicked();

  void on_pushButton_graph_clicked();

  void on_pushButton_exp_clicked();

 private:
  void append_text(const QString &text);

  void delete_last_sym();

 private:
  Ui::CalcWindow *ui;
  CreditWindow cred_window;
  DepositWindow dep_window;
  SmartGraph graph;

  my::Controller controller;

  bool was_x = false;
  bool zero_clicked = false;
};
#endif  // MAINWINDOW_H

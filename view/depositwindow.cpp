#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(my::Controller contr, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DepositWindow), controller(contr) {
  ui->setupUi(this);
  ui->comboBox_freq->lineEdit()->setAlignment(Qt::AlignCenter);
  ui->comboBox_term->lineEdit()->setAlignment(Qt::AlignCenter);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_pushButton_reset_clicked() {
  ui->input_amount->setText("");
  ui->input_interest->setText("");
  ui->input_replen->setText("");
  ui->input_tax->setText("");
  ui->input_term->setText("");
  ui->input_withdraw->setText("");
  ui->comboBox_term->lineEdit()->setText("Year(s)");
  ui->comboBox_freq->lineEdit()->setText("Once a month");
  ui->label_res_interest->setText("");
  ui->label_res_tax->setText("");
  ui->label_res_revenue->setText("");
  ui->checkBox_capital->setChecked(false);
}

void DepositWindow::reset_window() { on_pushButton_reset_clicked(); }

void DepositWindow::on_pushButton_calculate_clicked() {
  my::deposit_context context;
  context.amount = ui->input_amount->text().toStdString();
  context.interest = ui->input_interest->text().toStdString();
  context.tax = ui->input_tax->text().toStdString();
  context.freq = ui->comboBox_freq->lineEdit()->text().toStdString();
  context.term = ui->input_term->text().toStdString();
  context.withdrawal = ui->input_withdraw->text().toStdString();
  context.replenish = ui->input_replen->text().toStdString();
  context.capital = ui->checkBox_capital->isChecked();
  context.term_type = ui->comboBox_term->lineEdit()->text().toStdString();

  try {
    controller.DepositSolve(context);
  } catch (std::runtime_error &) {
    context.error = 1;
  }

  if (context.error != true) {
    ui->label_res_interest->setText(
        QString::number(static_cast<double>(context.res_interest)));
    ui->label_res_revenue->setText(
        QString::number(static_cast<double>(context.res_revenue)));
    ui->label_res_tax->setText(
        QString::number(static_cast<double>(context.res_tax)));
  } else {
    ui->label_res_interest->setText("Error");
    ui->label_res_revenue->setText("Error");
    ui->label_res_tax->setText("Error");
  }
}

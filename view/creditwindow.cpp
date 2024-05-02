#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(my::Controller contr, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditWindow), controller(contr) {
  ui->setupUi(this);
  ui->comboBox_term->lineEdit()->setReadOnly(true);
  ui->comboBox_term->lineEdit()->setAlignment(Qt::AlignCenter);
  ui->comboBox_type->lineEdit()->setReadOnly(true);
  ui->comboBox_type->lineEdit()->setAlignment(Qt::AlignHCenter);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_comboBox_type_currentIndexChanged() {
  QString cur = ui->comboBox_type->lineEdit()->text();
  if (!cur.compare("Annuity"))
    ui->label_payments->setText("Monthly payments:");
  else
    ui->label_payments->setText("First & last payments:");
}

void CreditWindow::on_pushButton_reset_clicked() {
  ui->input_amount->setText("");
  ui->input_interest->setText("");
  ui->input_term->setText("");
  ui->comboBox_type->lineEdit()->setText("Annuity");
  ui->comboBox_term->lineEdit()->setText("Year(s)");
  ui->label_overpay_res->setText("");
  ui->label_total_res->setText("");
  ui->label_payments_res->setText("");
  ui->label_payments->setText("Monthly payments:");
}

void CreditWindow::reset_window() { on_pushButton_reset_clicked(); }

void CreditWindow::on_pushButton_calculate_clicked() {
  my::credit_context cont;
  cont.amount = ui->input_amount->text().toStdString();
  cont.interest = ui->input_interest->text().toStdString();
  cont.months = ui->input_term->text().toStdString();
  cont.type = ui->comboBox_type->lineEdit()->text().toStdString();
  cont.term_type = ui->comboBox_term->lineEdit()->text().toStdString();

  try {
    controller.CreditSolve(cont);
  } catch (std::runtime_error &) {
    cont.error = true;
  }

  if (cont.error != true) {
    ui->label_overpay_res->setText(
        QString::number(static_cast<double>(cont.overpayment)));
    ui->label_total_res->setText(
        QString::number(static_cast<double>(cont.total_payment)));
    if (cont.type == "Annuity")
      ui->label_payments_res->setText(
          QString::number(static_cast<double>(cont.monthly_payment)));
    else {
      ui->label_payments_res->setText(
          QString::number(static_cast<double>(cont.first_payment)) + "\n" +
          QString::number(static_cast<double>(cont.last_payment)));
    }
  } else {
    ui->label_overpay_res->setText("Error");
    ui->label_total_res->setText("Error");
    ui->label_payments_res->setText("Error");
  }
}

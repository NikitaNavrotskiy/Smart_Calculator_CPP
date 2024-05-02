#include "mainwindow.h"

#include "ui_mainwindow.h"

CalcWindow::CalcWindow(my::Controller contr, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::CalcWindow),
      cred_window(contr),
      dep_window(contr),
      controller(contr) {
  ui->setupUi(this);
}

CalcWindow::~CalcWindow() { delete ui; }

void CalcWindow::on_pushButton_clearall_clicked() {
  ui->label_answer->setText("0");
  ui->input_x->setText("");
  was_x = false;
}

void CalcWindow::on_pushButton_openbrace_clicked() { append_text("("); }

void CalcWindow::on_pushButton_closebrace_clicked() { append_text(")"); }

void CalcWindow::on_pushButton_pow_clicked() { append_text("^"); }

void CalcWindow::on_pushButton_delete_clicked() {
  QString text = ui->label_answer->text();
  if (text.length() > 0 && text[text.length() - 1] == 'x') was_x = false;
  delete_last_sym();
}

void CalcWindow::on_pushButton_7_clicked() { append_text("7"); }

void CalcWindow::on_pushButton_8_clicked() { append_text("8"); }

void CalcWindow::on_pushButton_9_clicked() { append_text("9"); }

void CalcWindow::on_pushButton_div_clicked() { append_text("/"); }

void CalcWindow::on_pushButton_mod_clicked() { append_text("mod"); }

void CalcWindow::on_pushButton_4_clicked() { append_text("4"); }

void CalcWindow::on_pushButton_5_clicked() { append_text("5"); }

void CalcWindow::on_pushButton_6_clicked() { append_text("6"); }

void CalcWindow::on_pushButton_mul_clicked() { append_text("*"); }

void CalcWindow::on_pushButton_equal_clicked() {
  if (was_x == true && ui->input_x->text() == "")
    graph.DrawPlot(ui->label_answer->text());
  else {
    bool error = false;
    long double res =
        controller.CalcSolve(ui->label_answer->text().toStdString(),
                             ui->input_x->text().toStdString(), error);

    if (error) {
      if (was_x)
        graph.DrawPlot(ui->label_answer->text());
      else
        ui->label_answer->setText("Error");
    } else
      ui->label_answer->setText(QString::number(static_cast<double>(res)));
  }
}

void CalcWindow::on_pushButton_1_clicked() { append_text("1"); }

void CalcWindow::on_pushButton_2_clicked() { append_text("2"); }

void CalcWindow::on_pushButton_3_clicked() { append_text("3"); }

void CalcWindow::on_pushButton_sub_clicked() { append_text("-"); }

void CalcWindow::on_pushButton_0_clicked() {
  append_text("0");
  zero_clicked = true;
}

void CalcWindow::on_pushButton_dot_clicked() { append_text("."); }

void CalcWindow::on_pushButton_add_clicked() { append_text("+"); }

void CalcWindow::on_pushButton_sin_clicked() { append_text("sin("); }

void CalcWindow::on_pushButton_cos_clicked() { append_text("cos("); }

void CalcWindow::on_pushButton_tan_clicked() { append_text("tan("); }

void CalcWindow::on_pushButton_asin_clicked() { append_text("asin("); }

void CalcWindow::on_pushButton_acos_clicked() { append_text("asoc("); }

void CalcWindow::on_pushButton_atan_clicked() { append_text("atan("); }

void CalcWindow::on_pushButton_sqrt_clicked() { append_text("sqrt("); }

void CalcWindow::on_pushButton_log_clicked() { append_text("log10("); }

void CalcWindow::on_pushButton_ln_clicked() { append_text("ln("); }

void CalcWindow::on_pushButton_x_clicked() {
  append_text("x");
  was_x = true;
}

void CalcWindow::on_pushButton_exp_clicked() { append_text("e"); }

void CalcWindow::append_text(const QString& text) {
  QString old_str = ui->label_answer->text();
  QFontMetrics metrics(ui->label_answer->font());
  if ((zero_clicked == false && old_str == "0") || old_str == "Error")
    ui->label_answer->setText(text);
  else
    ui->label_answer->setText(metrics.elidedText(old_str + text, Qt::ElideLeft,
                                                 ui->label_answer->width()));
}

void CalcWindow::delete_last_sym() {
  QString old_text = ui->label_answer->text();
  qsizetype len = old_text.length();
  if (old_text != "0") {
    if (len > 1) {
      old_text.remove(len - 1, 1);
      ui->label_answer->setText(old_text);
    } else
      ui->label_answer->setText("0");
  }

  zero_clicked = false;
}

void CalcWindow::on_pushButton_credit_clicked() {
  cred_window.reset_window();
  cred_window.show();
}

void CalcWindow::on_pushButton_deposit_clicked() {
  dep_window.reset_window();
  dep_window.show();
}

void CalcWindow::on_pushButton_graph_clicked() { graph.show(); }

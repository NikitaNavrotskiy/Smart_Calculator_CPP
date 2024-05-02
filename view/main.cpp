#include <QApplication>

#include "../controller/controller.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  my::Controller controller;

  CalcWindow calc_window(controller);

  calc_window.show();

  return a.exec();
}

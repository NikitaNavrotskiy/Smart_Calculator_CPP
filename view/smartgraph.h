#ifndef SMARTGRAPH_H
#define SMARTGRAPH_H

#include <QMainWindow>
#include <QVector>

#include "../controller/controller.h"

namespace Ui {
class SmartGraph;
}

class SmartGraph : public QMainWindow {
  Q_OBJECT

 public:
  explicit SmartGraph(QWidget *parent = nullptr);
  ~SmartGraph();

  void DrawPlot(const QString &infix);

 private slots:
  void onMouseMove();

  void onMouseRelease();

 private:
  Ui::SmartGraph *ui;
  QVector<double> x, y;

  QString infix_cur;
  my::Controller controller;
  double eps = 0.01;
};

#endif  // SMARTGRAPH_H

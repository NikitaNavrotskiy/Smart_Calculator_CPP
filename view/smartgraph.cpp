#include "smartgraph.h"

#include "ui_smartgraph.h"

SmartGraph::SmartGraph(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SmartGraph) {
  ui->setupUi(this);

  connect(ui->widget, SIGNAL(mouseMove(QMouseEvent*)), this,
          SLOT(onMouseMove()));
  connect(ui->widget, SIGNAL(mouseRelease(QMouseEvent*)), this,
          SLOT(onMouseRelease()));

  for (double i = ui->widget->xAxis->range().lower;
       i < ui->widget->xAxis->range().upper; i += eps) {
    x.push_back(i);
    y.push_back(0);
  }
  ui->widget->addGraph()->setData(x, y);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom);
  ui->widget->setInteraction(QCP::iRangeDrag);
}

SmartGraph::~SmartGraph() { delete ui; }

void SmartGraph::DrawPlot(const QString& infix) {
  infix_cur = infix;
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  for (double x_ = ui->widget->xAxis->range().lower;
       x_ < ui->widget->xAxis->range().upper;
       x_ += eps * ui->widget->xAxis->range().size()) {
    bool error = false;
    double y_ = controller.CalcSolve(infix.toStdString(),
                                     QString::number(x_).toStdString(), error);

    if (!error && !isnanl(y_) && !isinfl(y_)) {
      x.append(x_);
      y.append(y_);
    }
  }

  ui->widget->addGraph()->setData(x, y);
  ui->widget->replot();
}

void SmartGraph::onMouseMove() { DrawPlot(infix_cur); }

void SmartGraph::onMouseRelease() { DrawPlot(infix_cur); }

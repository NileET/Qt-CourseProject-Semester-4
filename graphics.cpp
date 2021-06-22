#include "graphics.hpp"
#include "ui_graphics.h"

#include <QtCharts>

Graphics::Graphics(QList<Switch> switches, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Graphics),
   _switches(switches)
{
  ui->setupUi(this);
  resize(1200, 600);
}

Graphics::~Graphics()
{
  delete ui;
}

void Graphics::Price()
{
  setChart(Properties::price);
}

void Graphics::PortCount()
{
  setChart(Properties::portCount);
}

void Graphics::Volume()
{
  setChart(Properties::volume);
}

void Graphics::setChart(Properties prop)
{
  QBarSet* switchesBarSet[_switches.size()];
  QBarSeries* series = new QBarSeries();

  for (int i = 0; i < _switches.size(); ++i)
  {
      switchesBarSet[i] = new QBarSet(QString::fromStdString(_switches[i].getManufacturer() +
                                                             _switches[i].getModelName()));
      double number = 0;
      if (prop == Properties::price)
        number = _switches[i].getPrice();
      else if (prop == Properties::portCount)
        number = _switches[i].getPortCount();
      else {
          Switch::Size size = _switches[i].getModelSize();
          double volume = size.__width * size.__length * size.__high;
          number = volume;
        }
      *switchesBarSet[i] << number;
      series->append(switchesBarSet[i]);
  }

  QChart* chart = new QChart();
  chart->addSeries(series);
  if (prop == Properties::price)
    chart->setTitle(tr("Prices"));
  else if (prop == Properties::portCount)
    chart->setTitle(tr("Port Count"));
  else
    chart->setTitle(tr("Volume"));

  chart->setAnimationOptions(QChart::SeriesAnimations);

  QBarCategoryAxis* axisX = new QBarCategoryAxis();
  axisX->append("");
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis* axisY = new QValueAxis();
  if (prop == Properties::volume)
    axisY->setLabelFormat("%.1f");
  else
    axisY->setLabelFormat("%d");
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignRight);

  QChartView* chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(chartView);

  QWidget* price = new QWidget;
  price->setLayout(layout);

  ui->gridLayout->addWidget(price);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    drag = false;
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    setup();
    ui->customPlot->xAxis->setRange(50, 120, Qt::AlignHCenter);
    ui->customPlot->yAxis->setRange(50, 120, Qt::AlignHCenter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setup()
{
    wykres(ui->customPlot);
    setWindowTitle("Window with graph");
    statusBar()->clearMessage();
}

void MainWindow::wykres(QCustomPlot *customPlot)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setAntialiasedFill(false);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom  ); //zooming the graph
  customPlot->addGraph(); // red line
  customPlot->addGraph(); // blue dot
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);


    customPlot->legend->setVisible(true);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));

  //obsluga myszki do przesuwania wykresu
  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(1); // Interval 0 means to refresh as fast as possible

}


void MainWindow::realtimeDataSlot()
{
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  static double lastPointKey = 0;

  //random number
  int randomNumber = rand() % 100;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, randomNumber);

    // set data of dots:
    ui->customPlot->graph(2)->clearData(); // clear old dot
    ui->customPlot->graph(2)->addData(key, randomNumber);// graph new dot
    qDebug() << " realTimeDataSlot()";
    lastPointKey = key;
  }



  if (drag == false)
  {
      // make key axis range scroll with the data (at a constant range size of 8):
      ui->customPlot->xAxis->setRange(key+2.2, 8, Qt::AlignRight);

  }
    ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}


void MainWindow::mousePress(QMouseEvent*event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        drag = true;


    }
    if(event->buttons() != Qt::LeftButton)
    {
         drag = false;
         ui->customPlot->replot();
         ui->customPlot->update();
    }



}



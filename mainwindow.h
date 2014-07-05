#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool drag;
    void wykres(QCustomPlot *customPlot);
    void newGraph(QCustomPlot* customPlot);
    void setup();
private slots:
  void realtimeDataSlot();




  void on_actionNew_Graph_triggered(bool checked);

public slots:
  void mousePress(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;
};

#endif // MAINWINDOW_H

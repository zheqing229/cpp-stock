#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include "stockchinaclosearray.h"
#include <QVector>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PlotWindow; }
QT_END_NAMESPACE

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

    double aver(const StockChinaCloseArray& arr);
    double Pierce(const StockChinaCloseArray& arr1, const StockChinaCloseArray& arr2);

    double** loadfrom(const StockChinaCloseArray* pSCCA);

    void setPointer(double** p) { pd = p; }

    void showFigure();
private:
    Ui::PlotWindow *ui;

    //StockChinaCloseArray* pSCCA;

    double** pd;

    void draw(QCustomPlot* customPlot);
};
#endif // PLOTWINDOW_H

#ifndef KMEANSPLOTWINDOW_H
#define KMEANSPLOTWINDOW_H

#include "qcustomplot.h"
#include "stockmeanstd.h"
#include "ykmeans.h"
#include <QMainWindow>

namespace Ui {
class KmeansPlotWindow;
}

class KmeansPlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KmeansPlotWindow(QWidget *parent = nullptr);
    ~KmeansPlotWindow();

    void showFigure();

    void loadfrom(const StockMeanStD* pSMS);

    void setData();

    void setsize(int n) { size = n; }
private:
    Ui::KmeansPlotWindow *ui;

    //double** pdoubleArray;

    std::vector<std::vector<double>> doubleArr;//存储数据

    void draw(QCustomPlot* customPlot);

    KMEANS<double> kmeans;//类模板实例化

    int size;
};

#endif // KMEANSPLOTWINDOW_H

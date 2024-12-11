#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <fstream>
#include "stockchinaarray.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlotWindow; }
QT_END_NAMESPACE

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

    //从
    int loadFrom(StockChinaArray& Arr);
    //在窗体显示图形
    void showFigure(QString input);
private:
    Ui::PlotWindow *ui;

    //数据集
    QCPFinancialDataContainer data;
    //横轴刻度与标签信息
    QVector<QString> labels;
    QVector<double> ticks;
    //绘制蜡烛图
    void drawCandelSticks(QCustomPlot *customPlot);
};
#endif // PLOTWINDOW_H

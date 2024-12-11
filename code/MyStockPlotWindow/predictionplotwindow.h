#ifndef PREDICTIONPLOTWINDOW_H
#define PREDICTIONPLOTWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <fstream>
#include <QVector>
#include "stockchinaarray.h"
#include "linearregression.h"
#include "linearprogramming.h"

namespace Ui {
class PredictionPlotWindow;
}

class PredictionPlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PredictionPlotWindow(QWidget *parent = nullptr);
    ~PredictionPlotWindow();

    //从
    int loadFrom(StockChinaArray& Arr);
    //在窗体显示图形
    void showFigure(QString input);

    void LRprepare(StockChinaArray& Arr);//对前一个月进行线性回归得到w和b

    void LRpredict(StockChinaArray& Arr);//对这个月进行线性回归

    void LPrun();//线性规划

private:
    Ui::PredictionPlotWindow *ui;

    LinearRegression LR;//线性回归

    LinearProgramming LP;//线性规划
    //绘制
    void draw(QCustomPlot *customPlot);

    QVector<double> x;//这个月的日期
    QVector<double> y_pred1;//线性回归预测的价格
    QVector<double> y_pred2;//线性规划预测的价格
    QVector<double> y;//真实价格
    QVector<double> xx;//前一个月的日期
    QVector<double> yy;//前一个月的价格


};

#endif // PREDICTIONPLOTWINDOW_H

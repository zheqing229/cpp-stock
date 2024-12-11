#include "predictionplotwindow.h"
#include "ui_predictionplotwindow.h"
#include <string>
#include <QDebug>

PredictionPlotWindow::PredictionPlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PredictionPlotWindow)
{
    ui->setupUi(this);

    //设置窗体位置及大小
    setGeometry(200, 200, 1024, 668);
}

PredictionPlotWindow::~PredictionPlotWindow()
{
    delete ui;
}


///线性回归预处理
void PredictionPlotWindow::LRprepare(StockChinaArray& arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        xx.push_back(arr[i].dt2double());
        yy.push_back(arr[i].getClose());
    }


    LR.setLearningRate(0.01);
    LR.setMaxIter(100);
    LR.initialize();
    //qDebug() << LR.getB() << ' ' << LR.getW() << '\n';

    LR.fit(xx, yy);
    //qDebug() << LR.getB() << ' ' << LR.getW() << '\n';
}

void PredictionPlotWindow::LRpredict(StockChinaArray& arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        x.push_back(arr[i].dt2double());
        y.push_back(arr[i].getClose());

        y_pred1 = LR.fit(x, y);
    }
    /*for (int j = 0; j < y.size(); j ++)
    {
        qDebug() << y[j] << ' ' << y_pred[j] << '\n';
    }*/
}

void PredictionPlotWindow::LPrun()
{
    LP.calculate(xx, yy);///由上个月的数据获得初始的参数


    QVector<double> x_lp, y_lp;
    for (int i = 0; i < x.size(); i++)
    {
        x_lp.push_back(x[i]);
        y_lp.push_back(y[i]);

        LP.calculate(x_lp, y_lp);///读入这个月的一个新数据更新一次参数
        y_pred2.push_back(LP.predict(x[i]));///获得预测值并添加到预测值数组
    }
}

void PredictionPlotWindow::showFigure(QString input)
{
    draw(ui->customPlot);

    setWindowTitle("折线图 " + input);
    statusBar()->clearMessage();
    ui->customPlot->replot();
}


void PredictionPlotWindow::draw(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    customPlot->graph(0)->setName("Real Data"); //曲线名称
    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle::lsLine));  // 线段风格
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssPlus,5));//设置散点形状 "+"

    customPlot->addGraph();//添加graph等价于添加一条新曲线
    customPlot->graph(1)->setPen(QPen(Qt::red)); // 曲线的颜色
    customPlot->graph(1)->setName("Prediction1:Linear Regression"); //曲线名称
    customPlot->graph(1)->setLineStyle((QCPGraph::LineStyle::lsLine));  // 线段风格
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssCircle,5));//设置散点形状 "。"

    customPlot->addGraph();//添加graph等价于添加一条新曲线
    customPlot->graph(2)->setPen(QPen(Qt::green)); // 曲线的颜色
    customPlot->graph(2)->setName("Prediction2:Linear Programming"); //曲线名称
    customPlot->graph(2)->setLineStyle((QCPGraph::LineStyle::lsLine));  // 线段风格
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssCross,5));//设置散点形状 "."

    customPlot->legend->setVisible(true); // 显示图例

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // 把已存在的数据填充进graph的数据区
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(1)->setData(x, y_pred1);
    customPlot->graph(2)->setData(x, y_pred2);
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点（下面会单独讲到这个函数）
    customPlot->graph(0)->rescaleAxes();
    //自动调整XY轴的范围，以便显示出graph(1)中所有的点
    customPlot->graph(1)->rescaleAxes(true);
    //自动调整XY轴的范围，以便显示出graph(2)中所有的点
    customPlot->graph(2)->rescaleAxes(true);
    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // 立即刷新图像
    ui->customPlot->replot();

}

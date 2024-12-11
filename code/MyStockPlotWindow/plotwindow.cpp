#include <iostream>
#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    //设置窗体位置及大小
    setGeometry(200, 200, 1024, 668);

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

int PlotWindow::loadFrom(StockChinaArray& Arr)
{
    int count = 0;
    std::string sdate, last_date;
    std::string sdata;
    QCPFinancialData CHStockR;
    double* pO = &CHStockR.open;
    double* pH = &CHStockR.high;
    double* pL = &CHStockR.low;
    double* pC = &CHStockR.close;

    for (int i = 0; i < Arr.getSize(); i++)
    {
        sdate = Arr[i].dt();

        *pO = Arr[i].getOpen();
        *pH = Arr[i].getHigh();
        *pL = Arr[i].getLow();
        *pC = Arr[i].getClose();

        count++;
        CHStockR.key = count; //递增编号，作为横轴的值
        data.add(CHStockR);   //加入容器

        if((count == 1) || (count % 5 == 0))
        {//第1个数，每5个(天）打一个刻度标签
            labels << sdate.c_str(); ticks << count;
        }
        last_date = sdate;
    }
    if(!((count == 1) || (count % 15 == 0)))
    {//最后一个数也打上刻度标签
        labels << last_date.c_str(); ticks << count;
    }
    return count;

}

void PlotWindow::showFigure(QString input)
{
    drawCandelSticks(ui->customPlot);

    setWindowTitle("K线图 " + input);
    statusBar()->clearMessage();
    ui->customPlot->replot();
}


void PlotWindow::drawCandelSticks(QCustomPlot *customPlot)
{
    //customPlot->legend->setVisible(true);
    //设置数据，绘制图形
    QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis,
                                                  customPlot->yAxis);
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->data()->set(data);
    candlesticks->setWidth(0.9); //横轴数据单位为 1
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(240, 40, 50));
    candlesticks->setBrushNegative(QColor(10, 200, 50));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    //刻度标签
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(75); //刻度标签偏转角度
    customPlot->xAxis->setSubTicks(false);
    //customPlot->xAxis->setRange(0, 350);

    //比例迟适配，视图布局居中
    customPlot->rescaleAxes();
    customPlot->xAxis->scaleRange(1.05, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.45, customPlot->yAxis->range().center());

    //设置响应的交互事件：拖放，滚轮缩放。更详细的参见 专门的 interactions 项目示例
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

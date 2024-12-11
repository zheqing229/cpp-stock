#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <cmath>

PlotWindow::PlotWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlotWindow)
    , pd(NULL)
{
    ui->setupUi(this);
}

PlotWindow::~PlotWindow()
{
    delete ui;
    if (pd != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            delete[] pd[i];
        }
        delete[] pd;
    }
}

double PlotWindow::aver(const StockChinaCloseArray& arr)
{
    double sum = 0;
    for (int i = 0; i < arr.getSize(); i++)
    {
        sum += arr[i].getRate();
    }
    //qDebug() << "average:" << sum / arr.getSize() << '\n';
    return sum / arr.getSize();
}

///计算皮尔斯系数
double PlotWindow::Pierce(const StockChinaCloseArray& arr1, const StockChinaCloseArray& arr2)
{
    double sum12 = 0, sum1 = 0, sum2 = 0;
    double aver1, aver2;
    int n = (arr1.getSize() > arr2.getSize()) ?
                arr2.getSize() : arr1.getSize();
    aver1 = aver(arr1);
    aver2 = aver(arr2);
    for (int i = 0; i < n; i++)
    {
        sum12 += (arr1[i].getRate() - aver1) * (arr2[i].getRate() - aver2);
        sum1 += (arr1[i].getRate() - aver1) * (arr1[i].getRate() - aver1);
        sum2 += (arr2[i].getRate() - aver2) * (arr2[i].getRate() - aver2);
    }
    double pierce = sum12 / (std::sqrt(sum1) * std::sqrt(sum2));
    //qDebug() << "piece:" << pierce << '\n';
    return pierce;
}

double** PlotWindow::loadfrom(const StockChinaCloseArray* pSCCA)
{
    double** pdouble = new double* [10];//建立10*10方针
    for (int i = 0; i < 10; i++)
    {
        pdouble[i] = new double [10];
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
           pdouble[i][j] = Pierce(pSCCA[i], pSCCA[j]);//计算皮尔斯系数
        }
    }
    return pdouble;
}

void PlotWindow::showFigure()
{
    draw(ui->customPlot);

    /*for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            qDebug() << pd[i][j] << ' ';
            if (j == 9)
                qDebug() << '\n';
        }
    }
    */

    setWindowTitle("热力图 ");
    statusBar()->clearMessage();
    ui->customPlot->replot();
}

void PlotWindow::draw(QCustomPlot* customPlot)
{
    // 创建并添加热力图到绘图区域
    QCPColorMap* colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    //customPlot->addPlottable(colorMap);

    // 设置热力图的数据
    colorMap->data()->setSize(10, 10);
    colorMap->data()->setRange(QCPRange(0.0, 9.0), QCPRange(0.0, 9.0)); // 设置数据范围
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            colorMap->data()->setCell(i, j, pd[i][j]);
        }
    }



    // 设置每个单元格的标签
    QCPItemText* textElement;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            double value = pd[i][j];
            textElement = new QCPItemText(customPlot);
            textElement->position->setCoords(j, i); // 设置文本元素的位置
            textElement->setPositionAlignment(Qt::AlignCenter); // 设置文本元素的对齐方式
            textElement->setText(QLocale::system().toString(value, 'f', 2));
        }
    }


    // 创建颜色刻度栏
    QCPColorScale* colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // 将颜色刻度栏添加到绘图布局中
    colorScale->setType(QCPAxis::atRight); // 设置颜色刻度栏在右侧

    colorScale->setDataRange(QCPRange(0, 1));
    // 将热力图和颜色刻度栏绑定
    colorMap->setColorScale(colorScale);

    // 绘制热力图
    QCPMarginGroup* marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap->rescaleDataRange();
    customPlot->rescaleAxes();
    customPlot->replot();
}


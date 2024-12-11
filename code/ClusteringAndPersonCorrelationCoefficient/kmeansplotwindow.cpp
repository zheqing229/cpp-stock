#include "kmeansplotwindow.h"
#include "ui_kmeansplotwindow.h"
#include <QDebug>
#include <type_traits>

KmeansPlotWindow::KmeansPlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KmeansPlotWindow)
{
    ui->setupUi(this);

    setGeometry(10, 10, 400, 300);
}

KmeansPlotWindow::~KmeansPlotWindow()
{
    delete ui;
    /*if (!pdoubleArray)
    {
        for (int i = 0; i < std::extent<decltype(*pdoubleArray)>::value; i++)
        {
            delete[] pdoubleArray[i];
            pdoubleArray[i] = NULL;
        }
        delete [] pdoubleArray;
        pdoubleArray = NULL;
    }*/
}

void KmeansPlotWindow::loadfrom(const StockMeanStD* pSMS)
{
    for (int i = 0; i < size; i++)
    {
        std::vector<double> vec(2, 0);
        vec[0] = pSMS[i].getMean();
        vec[1] = pSMS[i].getStD();
        //if (pSMS[i].Sym() == "600519_SH") continue;//qDebug() << QString::fromStdString(pSMS[i].Sym());
        doubleArr.push_back(vec);
    }
}

void KmeansPlotWindow::showFigure()
{
    setData();
    draw(ui->customPlot);

    setWindowTitle("K-Means聚类散点图 ");
    statusBar()->clearMessage();
    ui->customPlot->replot();
}

void KmeansPlotWindow::setData()
{
    //数据加载入算法
    kmeans.loadData(doubleArr);
    qDebug() << "loaddata finished!" << '\n';
    //运行k均值聚类算法
    int clustercount = 9;
    kmeans.kmeans(clustercount);
    qDebug() << "kmeans finished!" << '\n';
}


void KmeansPlotWindow::draw(QCustomPlot* customPlot)
{
    // 获取数据的最小值和最大值，用于设置坐标轴范围
    double xMin = std::numeric_limits<double>::max();
    double xMax = std::numeric_limits<double>::lowest();
    double yMin = std::numeric_limits<double>::max();
    double yMax = std::numeric_limits<double>::lowest();

     // 遍历数据，找到最小值和最大值
    for (int i = 0; i < size; i++)
    {
        xMin = (xMin < doubleArr[i][0]) ? xMin : doubleArr[i][0];
        xMax = (xMax > doubleArr[i][0]) ? xMax : doubleArr[i][0];
        yMin = (yMin < doubleArr[i][1]) ? yMin : doubleArr[i][1];
        yMax = (yMax > doubleArr[i][1]) ? yMax : doubleArr[i][1];

    }
    qDebug() << xMin << ' ' << xMax << ' ' << yMin << ' ' << yMax << '\n';
    // 设置坐标轴范围
    customPlot->xAxis->setRange(xMin - 1, xMax + 1);
    customPlot->yAxis->setRange(yMin - 1, yMax + 1);

    // 获取k-means结果的聚类数
    int k = 9;

    // 创建一个颜色列表，用于为每个簇分配不同的颜色
    QVector<QColor> colors;
    colors << Qt::red << Qt::green << Qt::blue << Qt::cyan << Qt::magenta << Qt::darkYellow << Qt::darkRed << Qt::darkGreen << Qt::darkBlue;

    // 遍历每个簇，绘制对应的数据点
    for (int i = 0; i < k; ++i)
    {
        // 创建一个新的QCPGraph对象
        QCPGraph *scatterGraph = customPlot->addGraph();
        //scatterGraph->setScatterStyle(QCPScatterStyle::ssCircle);

        //scatterGraph->setPen(Qt::NoPen);
        // 设置画笔风格
        QPen drawPen;


        // 设置数据点的颜色
        QColor color = colors[i % colors.size()];
        //scatterGraph->setBrush(color);
        drawPen.setColor(color);
        drawPen.setWidth(4);
        scatterGraph->setPen(drawPen);
        scatterGraph->setLineStyle(QCPGraph::lsNone);
        scatterGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 2));
        // 遍历数据，将属于当前簇的点添加到图形对象中
        for (int j = 0; j < size; j++)
        {
            if (kmeans.clusterAssment[j].minIndex == i)
            {
                scatterGraph->addData(kmeans.dataSet[j][0], kmeans.dataSet[j][1]);
                //qDebug() << kmeans.clusterAssment[j].minIndex << ' ' << kmeans.dataSet[j][0] << ' ' << kmeans.dataSet[j][1] << '\n';
            }
        }
        //scatterGraph->setScatterStyle(QCPScatterStyle::ssCross);
        //scatterGraph->addData(kmeans.centroids[i][0], kmeans.centroids[i][1]);
        //qDebug() << "Centroid" << i << " " << kmeans.centroids[i][0] << ' ' << kmeans.centroids[i][1] << '\n';
        customPlot->graph()->rescaleAxes(true);
    }


    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // 更新绘图
    customPlot->replot();
}

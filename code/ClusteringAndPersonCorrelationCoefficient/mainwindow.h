#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "indexstockarray.h"
#include <QVector>
#include "stockchinaclosearray.h"
#include "plotwindow.h"
#include "stockmeanstd.h"
#include "kmeansplotwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void setIndexArr(const IndexStockArray& arr);

    QString getStockinaMonth(QString input);

    void buildArr(std::string input);

    void prepareKMeans();

private slots:
    void on_firstCommitButton_clicked();

    void on_secondCommitButton_clicked();

    void on_cancelButton_clicked();

    void on_thirdCommitButton_clicked();

private:
    Ui::MainWindow *ui;

    IndexStockArray isArr; //存储找到的该月股票和位置
    IndexStockArray indexArr;//所有的索引
    int number;

    QString wordInput;//用户输入的月份和股票

    StockChinaCloseArray* pSCCA;//数组指针

    PlotWindow* pw;//画热力图
    KmeansPlotWindow* kmpw;//画散点图

    StockMeanStD* pSMS;//（平均值，标准差）数组指针



};
#endif // MAINWINDOW_H

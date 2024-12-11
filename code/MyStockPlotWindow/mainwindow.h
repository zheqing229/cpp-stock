#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "indexstockarray.h"
#include "stockchinaarray.h"
#include <plotwindow.h>
#include <predictionplotwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(IndexStockArray& arr,QWidget *parent = nullptr);
    ~MainWindow();

    int CommitClick(std::string input);

    void setIndexArr(const IndexStockArray& arr);

private slots:
    void on_commitButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::MainWindow *ui;

    PlotWindow *pw;

    PredictionPlotWindow *ppw;

    IndexStockArray indexArr;
    StockChinaArray aStArr;//存储一支股票在这个月的数据
    StockChinaArray preStArr;//存储该股票前一个月的数据进行预测

    std::string filepath;//"D:\\stock_data\\bigdataCh\\ASCSorted_output_China.csv"
};

#endif // MAINWINDOW_H

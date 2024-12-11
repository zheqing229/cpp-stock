#include "plotwindow.h"
#include "mainwindow.h"
#include "indexstockarray.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IndexStockArray indexArr;
    indexArr.loadFrom("D:\\stock_data\\bigdataCh\\index.csv");


    //MainWindow mw(indexArr);
    MainWindow mw;
    mw.setIndexArr(indexArr);
    mw.show();
    //qDebug() << "mw set!" << '\n';


    return a.exec();
}

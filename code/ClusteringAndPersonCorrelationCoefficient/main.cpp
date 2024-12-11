#include "mainwindow.h"
#include "indexstockarray.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IndexStockArray indexArr;
    indexArr.loadFrom("D:\\stock\\index.csv");


    //MainWindow mw(indexArr);
    MainWindow mw;
    mw.setIndexArr(indexArr);
    mw.show();
    qDebug() << "SHOW!" << '\n';
    return a.exec();
}

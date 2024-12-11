#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    filepath("D:\\stock_data\\bigdataCh\\ASCSorted_output_China.csv")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_commitButton_clicked()
{
    QString wordInput = ui->InputlineEdit->text();
    std::string input = wordInput.toStdString();

    int n = CommitClick(input);
    qDebug() << n << '\n';

    if (!n)
    {
        QString str = "查询失败！未找到\n";
        ui->outputLineEdit->setText(str);
    }
    else
    {
        QString str = "查询成功！\n";
        ui->outputLineEdit->setText(str);

        QString title = QString::fromStdString(input);

        pw = new PlotWindow(this);

        pw->show();
        //qDebug() << "pw set!" <<'\n';

        pw->loadFrom(aStArr);
        pw->showFigure(title);

        ppw = new PredictionPlotWindow(this);

        ppw->show();

        ppw->LRprepare(preStArr);
        ppw->LRpredict(aStArr);
        ppw->LPrun();
        ppw->showFigure(title);
    }
}

int MainWindow::CommitClick(std::string input)
{
    std::string symbol, month;
    int pos = input.find(',');
    symbol.assign(input, 0, pos);
    month.assign(input, pos + 1, input.size());
    //qDebug() << QString::fromStdString(symbol) << ',' << QString::fromStdString(month) <<'\n';

    int startPos = 0;
    int endPos = 0;
    int previousPos = 0;
    int i = 1;
    for (i = 1; i < indexArr.getSize() - 2; i++)
    {
        if ((symbol != indexArr[i].sym()) || (month != indexArr[i].dt()))
            continue;
        previousPos = indexArr[i - 1].pos();
        startPos = indexArr[i].pos();
        endPos = indexArr[i + 1].pos();
        break;
    }

    //qDebug() << startPos << ',' << endPos << previousPos << '\n';a

    std::ifstream fileIN;
    fileIN.open(filepath,
                std::ios::in | std::ios::binary);

    std::string line;

    if (startPos != 0 && endPos != 0 && previousPos != 0)
    {
        // "1991-01-01,000001_SH,"21个字符
        //开始和结束的位置都往前退21个
        startPos -= 21;
        endPos -= 21;
        previousPos -= 21;
        fileIN.seekg(startPos, std::ios::beg);
        qDebug() << fileIN.tellg() <<'\n';
    }
    else if ((startPos == 0) &&
             (month == indexArr[indexArr.getSize() - 1].dt()) &&
             (symbol == indexArr[indexArr.getSize()-1].sym()))
    {
        startPos = indexArr[indexArr.getSize() - 1].pos();
        startPos -= 21;
        previousPos = indexArr[indexArr.getSize() - 2].pos();
        previousPos -= 21;
        fileIN.seekg(0, std::ios::end);
        // 获取当前读取位置的偏移量，即文件的末尾位置
        endPos = fileIN.tellg();
        fileIN.seekg(startPos, std::ios::beg);
    }
    else if ((previousPos == 0) &&
             (month == indexArr[0].dt()) &&
             (symbol == indexArr[0].sym()))
    {
        startPos = indexArr[0].pos();
        startPos -= 21;
        previousPos = 0;
        endPos = indexArr[1].pos();
        endPos -= 21;
        fileIN.seekg(startPos, std::ios::beg);
    }
    else return 0;

    aStArr.resize(0);
    preStArr.resize(0);
    int count = 0;
    while((!fileIN.eof()) && (fileIN.tellg() < endPos))
    {
        StockChina st;
        fileIN >> st;
        //qDebug() << QString::fromStdString(st.toString()) << '\n';
        aStArr.push_back(st);
        count++;
    }

    //qDebug() << aStArr.getSize() << '\n';
    //qDebug() << preStArr.getSize() << '\n';

    if ((symbol != indexArr[i-1].sym())) //股票在最开始的时候，没有上个月数据，直接返回
    {
        fileIN.close();
        return count;
    }

    fileIN.seekg(previousPos, std::ios::beg);
    while( (fileIN.tellg() < startPos) && (!fileIN.eof()))
    {
        StockChina st;
        fileIN >> st;
        //qDebug() << QString::fromStdString(st.toString()) << '\n';
        preStArr.push_back(st);
    }
    fileIN.close();
    return count;
}

void MainWindow::setIndexArr(const IndexStockArray& arr)
{
    indexArr = arr;
}

void MainWindow::on_cancelButton_clicked()
{
    this->close();
}


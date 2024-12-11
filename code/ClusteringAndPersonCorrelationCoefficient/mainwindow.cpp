#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "stockchinaclosearray.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pSCCA(NULL)
    , pw(NULL)
    , kmpw(NULL)
    , pSMS(NULL)
{
    ui->setupUi(this);
    indexArr.resize(0);
    isArr.resize(0);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (pSCCA != NULL)
    {
        delete[] pSCCA;
        pSCCA = NULL;
    }
    if (pw != NULL)
    {
        delete pw;
        pw = NULL;
    }
    if (pSMS != NULL)
    {
        delete[] pSMS;
        pSMS = NULL;
    }
    if (kmpw != NULL)
    {
        delete kmpw;
        kmpw = NULL;
    }
}


void MainWindow::setIndexArr(const IndexStockArray& arr)
{
    indexArr = arr;
}


QString MainWindow::getStockinaMonth(QString input)
{
    std::string month = input.toStdString();

    isArr.resize(0);

    for (int i = 0; i < indexArr.getSize(); i++)
    {
        if (month == indexArr[i].dt())
        {
            isArr.push_back(indexArr[i]);
            //qDebug() << QString::fromStdString(indexArr[i].toString()) << '\n';
        }
    }

    QString output;

    if (isArr.getSize() == 0)
        return "查询失败!";

    for (int i = 0; i < isArr.getSize(); i++)
    {
        output += QString::fromStdString(isArr[i].sym()) + '\n';
    }
    return output;
}


void MainWindow::on_firstCommitButton_clicked()
{
    wordInput = ui->inputLineEdit->text();

    QString output = getStockinaMonth(wordInput);

    ui->outputTextEdit->setText(output);

    prepareKMeans();

}


void MainWindow::on_secondCommitButton_clicked()
{
    QString txtInput = ui->inputTextEdit->toPlainText();

    std::string input = txtInput.toStdString();

    buildArr(input);

    pw = new PlotWindow;
    pw->show();
    pw->setPointer(pw->loadfrom(pSCCA));
    pw->showFigure();
    //qDebug() << "DONE!" << '\n';
}

void MainWindow::buildArr(std::string input)
{
    std::istringstream iss(input);

    //qDebug() << QString::fromStdString(input)<< '\n';

    std::string mon;
    mon = wordInput.toStdString();

    std::ifstream fileIN;
    fileIN.open("D:\\stock_data\\bigdataCh\\ASCSorted_output_China.csv",
                std::ios::in | std::ios::binary);

    //stArr.resize(0);
    pSCCA = new StockChinaCloseArray[10];

    for (int i = 0; i < 10; i++)
    {
        StockChinaCloseArray stArr(0);
        std::string s;
        std::getline(iss, s);
        if ((s[s.length() - 1] == '\r') || (s[s.length() - 1] == '\n'))
            s[s.length() - 1] = '\0';
        //qDebug() << QString::fromStdString(s) << '\n';

        for (int j = 0; j < isArr.getSize(); j++)
        {
            if (isArr[j].sym() == s)
            {
                stArr.resize(0, false);
                int pos = isArr[j].pos();
                pos -= 21; //退回这一行的开头
                fileIN.seekg(pos, std::ios::beg);
                //qDebug() << fileIN.tellg() << '\n';
                while (!fileIN.eof())
                {
                    StockChinaClose st;
                    fileIN >> st;
                    std::string stmon;
                    stmon = st.dt2mon();
                    if ((st.sym() == s) && (stmon == mon))
                    {
                        stArr.push_back(st);

                    }
                    else break;
                }
                for (int k = 1; k < stArr.getSize(); k++)
                {
                    double d = stArr[k] / stArr[k - 1];
                    stArr[k].setRate(d);
                    //qDebug() << QString::fromStdString(stArr[k].toString()) << '\n';
                }
                pSCCA[i] = stArr;
                break;
            }
        }
    }


    fileIN.close();
}

void MainWindow::prepareKMeans()
{
    std::string mon;//用户输入
    mon = wordInput.toStdString();

    std::ifstream fileIN;
    fileIN.open("D:\\stock_data\\bigdataCh\\ASCSorted_output_China.csv",
                std::ios::in | std::ios::binary);

    int size = isArr.getSize();
    pSMS = new StockMeanStD[size];

    for (int i = 0; i < isArr.getSize(); i++)
    {
        StockChinaCloseArray stArr;
        stArr.resize(0, false);
        int pos = isArr[i].pos();
        pos -= 21; //退回这一行的开头
        fileIN.seekg(pos, std::ios::beg);

        while (!fileIN.eof())
        {
            StockChinaClose st;
            fileIN >> st;
            std::string stmon;
            stmon = st.dt2mon();
            if ((st.sym() == isArr[i].sym()) && (stmon == mon))
            {
                stArr.push_back(st);
            }
            else break;
        }
        pSMS[i].loadfrom(stArr);
        //qDebug() << QString::fromStdString(pSMS[i].toString()) << '\n';
    }
    fileIN.close();
    number = isArr.getSize();
    qDebug() << isArr.getSize() << '\n';
}


void MainWindow::on_cancelButton_clicked()
{
    this->close();
}


void MainWindow::on_thirdCommitButton_clicked()
{
    kmpw = new KmeansPlotWindow;
    kmpw->show();
    kmpw->setsize(number);
    kmpw->loadfrom(pSMS);
    kmpw->showFigure();
}


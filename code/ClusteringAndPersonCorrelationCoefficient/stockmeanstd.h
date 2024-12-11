#ifndef STOCKMEANSTD_H
#define STOCKMEANSTD_H

#include <string>
#include "stockchinaclosearray.h"
#include "util.h"

class StockMeanStD
{
public:
    StockMeanStD();
    StockMeanStD(std::string sym, double m, double sd);
    StockMeanStD(const StockMeanStD& s);
    ~StockMeanStD();


    void loadfrom(const StockChinaCloseArray& arr);

    const StockMeanStD& operator=(const StockMeanStD& s);

    std::string toString();

    double getMean() const { return mean; }
    double getStD() const { return standardDeviation; }
    std::string Sym() const { return symbol; }

private:
    std::string symbol;
    double mean;
    double standardDeviation;//标准差

    double cal_mean(const StockChinaCloseArray& arr);//计算平均值
    double cal_standard_deviation(const StockChinaCloseArray& arr);//计算标准差

    void copyfrom(const StockMeanStD& s);
};

#endif // STOCKMEANSTD_H

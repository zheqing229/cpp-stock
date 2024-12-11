#include "stockmeanstd.h"
#include <cmath>

StockMeanStD::StockMeanStD() : symbol(""), mean(0), standardDeviation(0)
{

}

StockMeanStD::StockMeanStD(std::string s, double m, double sd):
    symbol(s)
  , mean(m)
  , standardDeviation(sd)
{

}

StockMeanStD::StockMeanStD(const StockMeanStD& s)
{
    copyfrom(s);
}

StockMeanStD::~StockMeanStD()
{

}

double StockMeanStD::cal_mean(const StockChinaCloseArray& arr)
{
    if (!arr.getSize()) return 0;
    double sum = 0.0;
    for (int i = 0; i < arr.getSize(); i++)
    {
        sum += arr[i].getClose();
    }
    return sum / arr.getSize();
}

double StockMeanStD::cal_standard_deviation(const StockChinaCloseArray& arr)
{
    if (!arr.getSize()) return 0;

    double sum = 0.0;
    for (int i = 0; i < arr.getSize(); i++)
    {
        sum += (arr[i].getClose() - mean) * (arr[i].getClose() - mean);
    }
    return std::sqrt(sum / arr.getSize());
}

void StockMeanStD::loadfrom(const StockChinaCloseArray& arr)
{
    if (!arr.getSize()) return;
    symbol = arr[0].sym();
    mean = cal_mean(arr);
    standardDeviation = cal_standard_deviation(arr);
}

void StockMeanStD::copyfrom(const StockMeanStD& s)
{
    symbol = s.symbol;
    mean = s.mean;
    mean = s.mean;
}

std::string StockMeanStD::toString()
{
    std::ostringstream oss;
    oss << symbol << ',';
    oss << Util::DoubleToString(mean, 4) << ',';
    oss << Util::DoubleToString(standardDeviation, 4) << '\n';

    return oss.str();
}

const StockMeanStD& StockMeanStD ::operator=(const StockMeanStD& s)
{
    copyfrom(s);
    return *this;
}

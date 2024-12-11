#ifndef STOCKCHINACLOSE_H
#define STOCKCHINACLOSE_H

#include <string>
//#include "util.h"

class StockChinaClose
{
public:
    StockChinaClose();
    StockChinaClose(std::string dt, std::string sym, double c);
    StockChinaClose(const StockChinaClose& sc);
    ~StockChinaClose();

    std::string getDatetime() const { return datetime; }
    void setDatetime(const std::string& s) { datetime = s; }

    std::string getSymbol() const { return symbol; }
    void setSymbol(const std::string& s) { symbol = s; }

    double getClose()const { return close; }
    void setClose(double d) { close = d; }

    double getRate() const { return rate; }
    void setRate(double d) { rate = d; }

    const StockChinaClose& operator=(const StockChinaClose& stc);

    double operator / (const StockChinaClose& sc);

    std::string toString() const;

    std::string sym() const;
    std::string dt() const;

    std::string dt2mon();

    double dt2double();

    friend std::ifstream& operator >> (std::ifstream& in,
        StockChinaClose& st);
    friend std::ofstream& operator << (std::ofstream& out,
        const StockChinaClose& st);



private:
    std::string datetime;
    std::string symbol;
    double close;
    double rate;

    //从文件流中读入【当前行】数据到节点中
    void readline(std::ifstream& in);
    //将节点数据写入文件
    void write(std::ofstream& out) const;

    void copyfrom(const StockChinaClose& sc);
};

#endif // STOCKCHINACLOSE_H

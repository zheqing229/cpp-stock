#ifndef STOCKCHINA_H
#define STOCKCHINA_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class StockChina
{
public:
    StockChina();
    StockChina(std::string dt, std::string sym, double o, double h, double l, double c);
    StockChina(const StockChina& sc);
    ~StockChina();

    std::string getDatetime() const { return datetime; }
    void setDatetime(const std::string& s) { datetime = s; }

    std::string getSymbol() const { return symbol; }
    void setSymbol(const std::string& s) { symbol = s; }

    double getOpen() const { return open; }
    void setOpen(double d) { open = d; }

    double getHigh() const { return high; }
    void setHigh(double d) { high = d; }

    double getLow()const { return low; }
    void setLow(double d) { low = d; }

    double getClose()const { return close; }
    void setClose(double d) { close = d; }


    const StockChina& operator=(const StockChina& stc);

    std::string toString() const;

    std::string sym() const;
    std::string dt() const;

    double dt2double();

    friend std::ifstream& operator >> (std::ifstream& in,
        StockChina& st);
    friend std::ofstream& operator << (std::ofstream& out,
        const StockChina& st);


private:
    std::string datetime; //日期
    std::string symbol; //代码
    double open; // 开盘价
    double high; //最高价
    double low; //最低价
    double close; //收盘价

    //从文件流中读入【当前行】数据到节点中
    void readline(std::ifstream& in);
    //将节点数据写入文件
    void write(std::ofstream& out) const;

    void copyfrom(const StockChina& sc);
};



#endif //STOCKCHINA_H

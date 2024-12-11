#ifndef STOCKUS_H
#define STOCKUS_H
#include "stock.h"
#include "util.h"

class StockUS : public Stock
{
public:
    StockUS();
    StockUS(const StockUS& sus);
    StockUS(double adjc, std::string dt, std::string sym,
        double o, double h, double l, double c, double v);
    ~StockUS();

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

    double getVolume()const { return volume; }
    void setVolume(double i) { volume = i; }


    const StockUS& operator=(const StockUS& szh);
    const Stock& operator =(const Stock& st);

    std::string toString() const;

    std::string sym() const;
    std::string dt() const;

    friend std::ifstream& operator >> (std::ifstream& in,
        Stock& st);
    friend std::ofstream& operator << (std::ofstream& out,
        const Stock& st);


private:
    std::string datetime;
    std::string symbol;
    double open;
    double high;
    double low;
    double close;
    double AdjClose;
    double volume;

    //从文件流中读入【当前行】数据到节点中
    void readline(std::ifstream& in);
    //将节点数据写入文件
    void write(std::ofstream& out) const;

    void copyfrom(const StockUS& sus);

    inline void checkAdjClose(std::ifstream& fileIN);
    //检查AdjClose是否异常
};

inline void StockUS::checkAdjClose(std::ifstream& fileIN)
{
    bool beNormal = fileIN.good();
    if (beNormal) return;

    fileIN.clear();

    fileIN.seekg(-1, std::ios::cur);//回滚一个位置
    char tc = fileIN.get();

    std::string tstr;
    getline(fileIN, tstr, ',');

    if (tstr == "inf")
    {
        if (tc == '-')
            AdjClose = NegInf;
        else
            AdjClose = Inf;
    }
    else
        AdjClose = NaN;
}


#endif // STOCKUS_H

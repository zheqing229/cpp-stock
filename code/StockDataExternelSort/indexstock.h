#ifndef INDEXSTOCK_H
#define INDEXSTOCK_H

#include "stock.h"

class IndexStock : public Stock
{
public:
    IndexStock();
    IndexStock(std::string symbol, std::string month);
    IndexStock(const IndexStock& ins);
    ~IndexStock();

    const Stock& operator = (const Stock& st);
    const IndexStock& operator=(const IndexStock& stc);

    std::string toString() const;

    std::string sym() const;
    std::string dt() const;

    friend std::ifstream& operator >> (std::ifstream& in, Stock& st);
    friend std::ofstream& operator << (std::ofstream& out, Stock& st);

private:
    std::string symbol;
    std::string month;
    int position;//保存open在文件中偏移量

    void readline(std::ifstream& in);
    void write(std::ofstream& out) const;

    std::string dt2mon(char* datetime);//将输入的日期转化成月份

    void copyfrom(const IndexStock& ins);
};

#endif // INDEXSTOCK_H

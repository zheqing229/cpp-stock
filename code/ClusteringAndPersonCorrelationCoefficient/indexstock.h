#ifndef INDEXSTOCK_H
#define INDEXSTOCK_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
class IndexStock
{
public:
    IndexStock();
    IndexStock(std::string symbol, std::string month);
    IndexStock(const IndexStock& ins);
    ~IndexStock();

    const IndexStock& operator=(const IndexStock& stc);

    std::string toString() const;

    std::string sym() const;
    std::string dt() const;
    int pos() const;

    friend std::ifstream& operator >> (std::ifstream& in, IndexStock& st);
    friend std::ofstream& operator << (std::ofstream& out, const IndexStock& st);

private:
    std::string symbol;
    std::string month;
    int position;

    void readline(std::ifstream& in);
    void write(std::ofstream& out) const;

    void copyfrom(const IndexStock& ins);
};

#endif // INDEXSTOCK_H

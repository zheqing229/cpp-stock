#include "indexstock.h"
#include <string>
#include <QDebug>

IndexStock::IndexStock(): symbol(""), month(""), position(0)
{

}

IndexStock::IndexStock(std::string symbol, std::string month):
    symbol(symbol), month(month), position(0)
{

}

IndexStock::IndexStock(const IndexStock& ins)
{
    copyfrom(ins);
}

IndexStock::~IndexStock()
{

}

void IndexStock::copyfrom(const IndexStock& ins)
{
    symbol = ins.symbol;
    month = ins.month;
    position = ins.position;
}

std::string IndexStock::dt() const
{
    return month;
}

std::string IndexStock::sym() const
{
    return symbol;
}

int IndexStock::pos() const
{
    return position;
}

std::string IndexStock::toString() const
{
    std::ostringstream oss;

    oss << symbol << ',';
    oss << month << ',';
    oss << position << '\n';

    return oss.str();
}

void IndexStock::write(std::ofstream& out) const
{
    out << toString();
}

const IndexStock& IndexStock::operator=(const IndexStock& ins)
{
    copyfrom(ins);
    return *this;
}

void IndexStock::readline(std::ifstream& fileIN)
{
    std::string line;
    std::getline(fileIN, line);


    std::istringstream iss(line);

    std::getline(iss, symbol, ',');
    std::getline(iss, month, ',');
    std::string value;
    std::getline(iss, value);
    position = std::stoi(value);
    //qDebug() << position << '\n';
}

std::ifstream& operator >> (std::ifstream& in, IndexStock& st)
{
    st.readline(in);
    return in;
}

std::ofstream& operator << (std::ofstream& out, const IndexStock& st)
{
    st.write(out);
    return out;
}

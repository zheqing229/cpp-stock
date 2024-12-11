#include "stockchina.h"
#include "util.h"

StockChina::StockChina() :datetime(""), symbol(""), open(0), high(0), close(0), low(0)
{
}

StockChina::StockChina(std::string dt, std::string sym, double o, double h, double l, double c) :
    datetime(dt),
    symbol(sym),
    open(o),
    high(h),
    low(l),
    close(c)
{
}

StockChina::StockChina(const StockChina& sc)
{
    copyfrom(sc);
}

StockChina::~StockChina()
{
}

const StockChina& StockChina::operator=(const StockChina& stc)
{
    copyfrom(stc);
    return *this;
}

std::string StockChina::toString() const
{
    std::ostringstream ostr;

    ostr << datetime << ',';
    ostr << symbol << ',';
    ostr << Util::DoubleToString(open, 2) << ',';
    ostr << Util::DoubleToString(high, 2) << ',';
    ostr << Util::DoubleToString(low, 2) << ',';
    ostr << Util::DoubleToString(close, 2) << ',';

    return ostr.str();
}

std::string StockChina::sym() const
{
    return symbol;
}

std::string StockChina::dt() const
{
    return datetime;
}


void StockChina::readline(std::ifstream& fileIN)
{
    std::string line;
    std::getline(fileIN, line);
    if (line.empty()) return;
    std::istringstream iss(line);

    Util util;

    std::string value;

    std::getline(iss, value, ',');
    datetime = value;

    std::getline(iss, value, ',');
    symbol = value;

    std::getline(iss, value, ',');
    open = util.convertValue(value);

    std::getline(iss, value, ',');
    high = util.convertValue(value);

    std::getline(iss, value, ',');
    low = util.convertValue(value);

    std::getline(iss, value, ',');
    close = util.convertValue(value);
}


void StockChina::write(std::ofstream& out) const
{
    out << toString();
}

void StockChina::copyfrom(const StockChina& sc)
{
    symbol = sc.symbol;
    datetime = sc.datetime;
    high = sc.high;
    low = sc.low;
    close = sc.close;
    open = sc.open;
}

std::ifstream& operator >> (std::ifstream& in,
        StockChina& st)
{
    st.readline(in);
    return in;
}

std::ofstream& operator << (std::ofstream& out,
        const StockChina& st)
{
    st.write(out);
    return out;
}


double StockChina::dt2double()
{
    std::string s;
    s.assign(datetime, 8, 9);
    return std::stod(s);
}

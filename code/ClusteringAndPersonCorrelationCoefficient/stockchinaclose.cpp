#include "stockchinaclose.h"
#include <sstream>
#include "util.h"
#include <fstream>

StockChinaClose::StockChinaClose() :datetime(""), symbol(""), close(0), rate(0)
{
}

StockChinaClose::StockChinaClose(std::string dt, std::string sym, double c) :
    datetime(dt),
    symbol(sym),
    close(c),
    rate(0)
{
}

StockChinaClose::StockChinaClose(const StockChinaClose& sc)
{
    copyfrom(sc);
}

StockChinaClose::~StockChinaClose()
{
}

const StockChinaClose& StockChinaClose::operator=(const StockChinaClose& stc)
{
    copyfrom(stc);
    return *this;
}

std::string StockChinaClose::toString() const
{
    std::ostringstream ostr;

    ostr << datetime << ',';
    ostr << symbol << ',';

    ostr << Util::DoubleToString(close, 2) << ',';
    ostr << "rate:" << Util::DoubleToString(rate, 5) << '\n';
    return ostr.str();
}

std::string StockChinaClose::sym() const
{
    return symbol;
}

std::string StockChinaClose::dt() const
{
    return datetime;
}


void StockChinaClose::readline(std::ifstream& fileIN)
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
    //open = util.convertValue(value);

    std::getline(iss, value, ',');
    //high = util.convertValue(value);

    std::getline(iss, value, ',');
    //low = util.convertValue(value);

    std::getline(iss, value, ',');
    close = util.convertValue(value);
}


void StockChinaClose::write(std::ofstream& out) const
{
    out << toString();
}

void StockChinaClose::copyfrom(const StockChinaClose& sc)
{
    symbol = sc.symbol;
    datetime = sc.datetime;

    close = sc.close;
    rate = sc.rate;
}

std::ifstream& operator >> (std::ifstream& in,
        StockChinaClose& st)
{
    st.readline(in);
    return in;
}

std::ofstream& operator << (std::ofstream& out,
        const StockChinaClose& st)
{
    st.write(out);
    return out;
}


double StockChinaClose::dt2double()
{
    std::string s;
    s.assign(datetime, 8, 9);
    return std::stod(s);
}

double StockChinaClose::operator/(const StockChinaClose& sc)
{
    return (close - sc.close) / sc.close;
}

std::string StockChinaClose::dt2mon()
{
    std::string s;
    for (int i = 0; i < 7; i++)
    {
        if (i == 4) continue;
        s += datetime[i];
    }
    return s;
}

#include "stockchina.h"
#include "util.h"

StockChina::StockChina() :datetime(""), symbol(""), open(0), high(0), close(0), low(0),
volume(0), UDamount(0), UDrate(0), transAmount(0), turnover(0), amplitude(0)
{
}

StockChina::StockChina(std::string dt, std::string sym, double o, double h, double l, double c,
    double UDA, double UDR, int v, int trA, double apl, double turnover) :
    datetime(dt),
    symbol(sym),
    open(o),
    high(h),
    close(c),
    low(l),
    volume(v),
    UDamount(UDA),
    UDrate(UDR),
    transAmount(trA),
    turnover(turnover),
    amplitude(apl)
{
}

StockChina::StockChina(const StockChina& sc) :Stock(sc.SrcID)
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

const Stock& StockChina::operator =(const Stock& st)
{
    /*if (typeid(StockChina) != typeid(Stock))
    {
        throw ("mismatched objects ...");
    }*/
    const StockChina& stcn = dynamic_cast<const StockChina&>(st);//类型强制转化

    *this = stcn;
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
    ostr << Util::DoubleToString(UDamount, 2) << ',';
    ostr << Util::DoubleToString(UDrate, 2) << ',';
    ostr << volume << ',';
    ostr << transAmount << ',';
    ostr << Util::DoubleToString(amplitude, 2) << ',';
    ostr << Util::DoubleToString(turnover, 2) << "\n";
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
    std::getline(fileIN, line);//获得整行
    if (line.empty()) return;
    std::istringstream iss(line);

    Util util;

    std::string value;

    std::getline(iss, value, ',');
    datetime = value;

    std::getline(iss, value, ',');
    symbol = value;

    //用convertValue检测“--”避免异常
    std::getline(iss, value, ',');
    open = util.convertValue(value);

    std::getline(iss, value, ',');
    high = util.convertValue(value);

    std::getline(iss, value, ',');
    low = util.convertValue(value);

    std::getline(iss, value, ',');
    close = util.convertValue(value);

    std::getline(iss, value, ',');
    UDamount = util.convertValue(value);

    std::getline(iss, value, ',');
    UDrate = util.convertValue(value);

    std::getline(iss, value, ',');
    volume = util.convertValue(value);

    std::getline(iss, value, ',');
    transAmount = util.convertValue(value);

    std::getline(iss, value, ',');
    amplitude = util.convertValue(value);

    std::getline(iss, value);
    turnover = util.convertValue(value);
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
    volume = sc.volume;
    UDamount = sc.UDamount;
    UDrate = sc.UDrate;
    transAmount = sc.transAmount;
    turnover = sc.turnover;
    amplitude = sc.amplitude;
    SrcID = sc.SrcID;
}

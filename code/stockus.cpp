#include "StockUS.h"
#include "util.h"


StockUS::StockUS():
    datetime(""), symbol(""), open(0), high(0), low(0),
    close(0), AdjClose(0), volume(0)
{
}

StockUS::StockUS(double adjc, std::string dt, std::string sym,
    double o, double h, double l, double c, double v):
    datetime(dt), symbol(sym), open(o), high(h), low(l),
    close(c), AdjClose(adjc), volume(v)
{

}

StockUS::StockUS(const StockUS& sus)
{
    copyfrom(sus);
}

StockUS::~StockUS()
{
}

const StockUS& StockUS::operator=(const StockUS& sus)
{
    copyfrom(sus);
    return *this;
}

const Stock& StockUS::operator =(const Stock& st)
{
    const StockUS& sus = dynamic_cast<const StockUS&>(st);

    *this = sus;
    return *this;
}

std::string StockUS::toString() const
{
    std::ostringstream ostr;

    ostr << datetime << ',';
    ostr << symbol << ',';
    ostr << Util::DoubleToString(open, 2) << ',';
    ostr << Util::DoubleToString(high, 2) << ',';
    ostr << Util::DoubleToString(low, 2) << ',';
    ostr << Util::DoubleToString(close, 2) << ",";
    ostr << Util::DoubleToString(AdjClose, 2) << ",";
    ostr << Util::DoubleToString(volume, 2) << '\n';

    return ostr.str();
}

std::string StockUS::sym() const
{
    return symbol;
}

std::string StockUS::dt() const
{
    return datetime;
}

void StockUS::readline(std::ifstream& fileIN)
{
    char field1st[100] = { 0 };
    int i = 0;
    char  comma; //分隔逗号

    //按序从文件流中向数据成员输入数据，并跳过逗号
    while (true)
    {
        field1st[i] = fileIN.get();
        //inFile >> field1st[i];

        //↑↑↑读到分隔符, 或文件流结束(文件末尾空行）
        if (field1st[i] == ',' || fileIN.eof())
            break;
        if (i == 99) continue;

        i++;
    }
    if (field1st[i] != ',') return; //首字段读失败
    field1st[i] = '\0';
    datetime = field1st;
    //读取日期结束

    i = 0;
    char field2nd[100] = { '\0' };
    while (true)
    {
        field2nd[i] = fileIN.get();

        //↑↑↑读到分隔符, 或文件流结束(文件末尾空行）
        if (field2nd[i] == ',' || fileIN.eof())
            break;

        if (i == 99) continue;

        i++;
    }
    if (field2nd[i] != ',') return; //首字段读失败
    field2nd[i] = '\0';
    symbol = field2nd;
    fileIN >> open >> comma;
    fileIN >> high >> comma;
    fileIN >> low >> comma;
    fileIN >> close >> comma;

    fileIN >> AdjClose >> comma;
    checkAdjClose(fileIN);

    fileIN >> volume;

}

void StockUS::write(std::ofstream& out) const
{
    out << toString();
}

void StockUS::copyfrom(const StockUS& sc)
{
    symbol = sc.symbol;
    datetime = sc.datetime;
    high = sc.high;
    low = sc.low;
    close = sc.close;
    open = sc.open;
    volume = sc.volume;
    AdjClose = sc.AdjClose;
    SrcID = sc.SrcID;
}

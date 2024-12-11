#include "indexstock.h"

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

const Stock& IndexStock::operator=(const Stock& st)
{
    const IndexStock& ins = dynamic_cast<const IndexStock&>(st);

    *this = ins;
    return *this;

}

void IndexStock::readline(std::ifstream& fileIN)
{
    char field1st[100] = { '\0' };
    int i = 0; //分隔逗号

    //按序从文件流中向数据成员输入数据，并跳过逗号
    while (true)
    {
        field1st[i] = fileIN.get();

        //↑↑↑读到分隔符, 或文件流结束(文件末尾空行）
        if (field1st[i] == ',' || fileIN.eof())
            break;
        if (i == 99) continue;

        i++;
    }
    if (field1st[i] != ',') return; //首字段读失败
    field1st[i] = '\0';
    month = dt2mon(field1st);
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

    position = fileIN.tellg();

    std::string line;
    getline(fileIN, line);
}

std::string IndexStock::dt2mon(char* datetime)
{
    std::string result;
    for (int i = 0; i < 7; i++)
        result.push_back(datetime[i]);
    result.erase(4, 1);
    return result;
}

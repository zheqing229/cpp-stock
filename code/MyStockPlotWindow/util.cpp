#include <iostream>
#include "util.h"

/*
独立的功能函数，部分是测试验证用途
*/

//把浮点数转换为字符串，保留小数的实际有效位数。
std::string Util::DoubleToString(const double value, unsigned int precisionAfterPoint)
{
    std::ostringstream out;
    // 清除默认精度
    out.precision(std::numeric_limits<double>::digits10);
    out << value;

    std::string res = out.str();
    auto pos = res.find('.');
    if (pos == std::string::npos)
        return res;

    auto splitLen = pos + 1 + precisionAfterPoint;
    if (res.size() <= splitLen)
        return res;

    return res.substr(0, splitLen);
}

//获取文件的行数
size_t Util::lineNumberInFile(std::ifstream& in, std::string& titleLine, bool haseTitleLine)
{
    if (!in.is_open()) { throw "the file is closed..."; }

    in.seekg(0, std::ios::beg); //将文件流的读取位置设置为文件的开头

    char line[401] = { 0 };
    size_t n = 0;
    size_t offset = 0;
    if (haseTitleLine)
    {//读取标题行
        in.getline(line, 400);
        offset = in.tellg(); //以二进制方式打开文本文件，定位才准确
        titleLine = line;
        //offset = titleLine.length();
    }
    else
    {
        titleLine = "";
    }

    while (!in.eof())
    {
        in.getline(line, 400);
        if (line[0] > 0) n++; //空行，特别是文件末尾有回车换行时，不计数
    }

    in.clear(); //扫描文件得到行数后，读取位置在 eof.
    in.seekg(offset, std::ios::beg); // 重置读取位置

    return n;
}

//字符串转换为数值(有相应的库函数）
int Util::strton(std::string& nstr)
{
    int n = 0;
    int len = nstr.length();
    for (int i = 0; i < len; i++)
    {
        if ((nstr[i] > '9') || (nstr[i] > '0')) return 0;
        n = n * 10 + (nstr[i] - '0');
    }
    return n;
}

//根据分隔符位置，取字段字符串
std::string Util::fieldStringAt(std::string row, int pos, char delim)
{
    int p = 0;
    int len = row.length();

    std::string fieldStr;
    for (int i = 0; i < len; i++)
    {
        if (row[i] == delim)
        {
            p++;
            continue;
        }

        if (p > pos) break;
        if (p < pos) continue;

        fieldStr.push_back(row[i]);
    }
    return fieldStr;
}

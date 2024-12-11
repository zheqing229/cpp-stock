#ifndef UTIL_H
#define UTIL_H

#include <limits>
#include <sstream>
#include "datadef.h"
#include <fstream>
#include "stock.h"

std::ifstream& operator >> (std::ifstream& in, Stock& st);
std::ofstream& operator << (std::ofstream& out, const Stock& st);

class Util
{

public:
    static std::string DoubleToString(const double value, unsigned int precisionAfterPoint);
    static size_t lineNumberInFile(std::ifstream& in, std::string& titleLine, bool haseTitleLine);

    static int strton(std::string& nstr);
    static std::string fieldStringAt(std::string row, int pos, char delim);

    // 辅助函数，将字符串转换为对应类型的值

    inline double convertValue(const std::string& value);

    //inline int convertValue(const std::string& value);
};

//int可转化为double
inline double Util::convertValue(const std::string& value)
{
    if (value == "--\r" || value == "--")
        return NaN;
    else
        return std::stod(value);
}


#endif // UTIL_H

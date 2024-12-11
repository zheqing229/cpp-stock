#ifndef STOCKCHINACLOSEARRAY_H
#define STOCKCHINACLOSEARRAY_H
#include "stockchinaclose.h"

class StockChinaCloseArray
{
public:
    StockChinaCloseArray(int size = 0);
    StockChinaCloseArray(const StockChinaCloseArray& arr);
    ~StockChinaCloseArray(); //负责动态分配空间的回收

    //从(大数据)文件流的[当前行]位置开始，批量加载数据
    int loadFrom(std::ifstream& fileIn, int s);
    //将动态数组中的全部数据保存到新文件
    void save(std::string filePath) const;

    //重整数据内存空间，默认拷贝原有数据
    void resize(int size, bool to_copy = true);

    StockChinaClose& operator [](int i); //读写
    const StockChinaClose& operator [](int i) const; //只读

    int getSize() const { return size; }
    void setSize(int s) { size = s; }

    //赋值运算符重载
    const StockChinaCloseArray& operator = (const StockChinaCloseArray& arr);
    //数据元素实际使用的内存空间
    int realDataBytes() const { return (sizeof(StockChinaClose) * size); }

    void push_back(const StockChinaClose& st);

private:
    StockChinaClose* pStockChinaClose;
    void copyFrom(const StockChinaCloseArray& arr);
    int size;

};

#endif // STOCKCHINACLOSEARRAY_H

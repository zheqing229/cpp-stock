#ifndef STOCKCHINAARRAY_H
#define STOCKCHINAARRAY_H

#include "stockchina.h"
class StockChinaArray
{
public:
    StockChinaArray(int size = 0);
    StockChinaArray(const StockChinaArray& arr);
    ~StockChinaArray(); //负责动态分配空间的回收

    //从(大数据)文件流的[当前行]位置开始，批量加载数据
    int loadFrom(std::ifstream& fileIn, int s);
    //将动态数组中的全部数据保存到新文件
    void save(std::string filePath) const;

    //重整数据内存空间，默认拷贝原有数据
    void resize(int size, bool to_copy = true);

    StockChina& operator [](int i); //读写
    const StockChina& operator [](int i) const; //只读

    int getSize() const { return size; }
    void setSize(int s) { size = s; }

    //赋值运算符重载
    const StockChinaArray& operator = (const StockChinaArray& arr);
    //数据元素实际使用的内存空间
    int realDataBytes() const { return (sizeof(StockChina) * size); }

    void push_back(const StockChina& st);

private:
    StockChina* pStockChina;
    void copyFrom(const StockChinaArray& arr);
    int size;

};

#endif //!STOCKCHINAARRAY_H


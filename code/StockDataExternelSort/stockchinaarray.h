#ifndef STOCKCHINAARRAY_H
#define STOCKCHINAARRAY_H

#include "stockarray.h"
#include "stockchina.h"
class StockChinaArray : public StockArray
{
public:
    StockChinaArray(int size = 0);
    StockChinaArray(const StockChinaArray& arr);
    ~StockChinaArray(); //负责动态分配空间的回收

    //从(大数据)文件流的[当前行]位置开始，批量加载数据
    int loadFrom(std::ifstream& fileIn);
    //将动态数组中的全部数据保存到新文件
    void save(std::string filePath) const;

    //重整数据内存空间，默认拷贝原有数据
    void resize(int size, bool to_copy = true);

    StockChina& operator [](int i) override; //读写
    const StockChina& operator [](int i) const override; //只读

    //赋值运算符重载
    const StockChinaArray& operator = (const StockChinaArray& arr);
    //数据元素实际使用的内存空间
    int realDataBytes() const { return (sizeof(StockChina) * size); }

    void display() const;

private:
    StockChina* pStockChina;
    void copyFrom(const StockChinaArray& arr);


};

#endif //!STOCKCHINAARRAY_H


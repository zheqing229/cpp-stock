#ifndef STOCKUSARRAY_H
#define STOCKUSARRAY_H
#include "stockarray.h"
#include "util.h"
#include "StockUS.h"
class StockUSArray :
    public StockArray
{
public:
    StockUSArray(int size = 0);
    StockUSArray(const StockUSArray& arr);
    ~StockUSArray(); //负责动态分配空间的回收

    //从(大数据)文件流的[当前行]位置开始，批量加载数据
    int loadFrom(std::ifstream& fileIn);
    //将动态数组中的全部数据保存到新文件
    void save(std::string filePath) const;

    //重整数据内存空间，默认拷贝原有数据
    void resize(int size, bool to_copy = true);

    StockUS& operator [](int i) override; //读写
    const StockUS& operator [](int i) const override; //只读

    //赋值运算符重载
    const StockUSArray& operator = (const StockUSArray& arr);
    //数据元素实际使用的内存空间
    int realDataBytes() const { return (sizeof(StockUS) * size); }

    void display() const;

private:
    StockUS* pStockUS;
    void copyFrom(const StockUSArray& arr);

};


#endif // !STOCKUSARRAY_H

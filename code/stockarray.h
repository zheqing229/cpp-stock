#ifndef STOCKARRAY_H
#define STOCKARRAY_H

#include "stock.h"

class StockArray
{
protected:
    int size;    //动态数组的大小，类族共享成员

public:
    StockArray(int size = 0) :size(size) { ; }
    virtual ~StockArray() { ; }

    virtual Stock& operator [](int i) = 0; //可以修改, 只读
    virtual const Stock& operator [](int i) const = 0;  //只读访问，不能修改

    int sizeOf() const { return size; }

    void setSize(int newSize) { size = newSize; }
};
#endif // STOCKARRAY_H

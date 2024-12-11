#ifndef INDEXSTOCKARRAY_H
#define INDEXSTOCKARRAY_H

#include "indexstock.h"

class IndexStockArray
{
public:
    IndexStockArray();
    IndexStockArray(const IndexStockArray& iarr);
    ~IndexStockArray();

    void setSize(int s) { size = s; }
    int getSize() const { return size; }

    IndexStock& operator [] (int i); //读写
    const IndexStock& operator[] (int i) const; // 只读

    const IndexStockArray& operator = (const IndexStockArray& arr);

    void loadFrom(std::string filePath);

    void push_back(const IndexStock& is);

    void resize(int newSize, bool to_copy = true);

private:
    IndexStock* pIndexStock;

    int size;

    void copyfrom(const IndexStockArray& iarr, bool toCopy = true);


};

#endif // INDEXSTOCKARRAY_H

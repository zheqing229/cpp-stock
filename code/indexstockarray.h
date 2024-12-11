#ifndef INDEXSTOCKARRAY_H
#define INDEXSTOCKARRAY_H

#include "stockarray.h"
#include "indexstock.h"

class IndexStockArray : public StockArray
{
public:
    IndexStockArray();
    IndexStockArray(std::string filePathIn);
    IndexStockArray(const IndexStockArray& iarr);
    ~IndexStockArray();

    void setFilePathIn(std::string);
    std::string getFilePathIn() const;

    void setFilePathOut(std::string);
    std::string getFilePathOut() const;

    void setHaseTitle(bool ht = true);
    bool getHaseTitle() const;

    IndexStock& operator [] (int i) override; //读写
    const IndexStock& operator[] (int i) const override; // 只读

    void run();

private:
    IndexStock* pIndexStock;//数组指针
    std::string filePathIn;
    std::string filePathOut;
    std::ofstream out;
    std::ifstream in;
    bool haseTitle;

    void copyfrom(const IndexStockArray& iarr, bool toCopy = true);

    void resize(int newSize);

};

#endif // INDEXSTOCKARRAY_H

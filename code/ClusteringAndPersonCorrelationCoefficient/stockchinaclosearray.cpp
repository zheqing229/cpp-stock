#include "stockchinaclosearray.h"
#include <iostream>
#include <fstream>

StockChinaCloseArray::StockChinaCloseArray(int size) :
    pStockChinaClose(NULL)
{
    pStockChinaClose = new StockChinaClose[size];
}

StockChinaCloseArray::StockChinaCloseArray(const StockChinaCloseArray& arr) :
    pStockChinaClose(NULL)
{
    if (size <= 0) return;
    pStockChinaClose = new StockChinaClose[size];
    copyFrom(arr);
}

StockChinaCloseArray::~StockChinaCloseArray()
{
    if (pStockChinaClose == NULL) return;

    delete[] pStockChinaClose;
    pStockChinaClose = NULL;
}

void StockChinaCloseArray::resize(int size, bool to_copy)
{
    if (this->size == size) return;
    ///////////////////////////////
    StockChinaClose* pNew = NULL;
    if (size > 0)
    {//分配新空间；截取数据
        pNew = new StockChinaClose[size];

        if (to_copy)//必要时才拷贝原始数据
        {
            int n = (size < this->size) ? size : this->size;
            for (int i = 0; i < n; i++)
            {
                pNew[i] = pStockChinaClose[i];
            }
        }
    }

    this->size = size;
    if (pStockChinaClose != NULL)
    {//释放原数据空间
        delete[] pStockChinaClose;
        pStockChinaClose = NULL;
    }

    pStockChinaClose = pNew;
}

int StockChinaCloseArray::loadFrom(std::ifstream& fileIn, int s)
{
    size = s;
    resize(size);
    size_t i = 0;
    for (; !fileIn.eof() && (i < size); i++)
    {
        fileIn >> pStockChinaClose[i];
        //std::cout << "Line_" << i << std::endl;
    }

    if (i < size) resize(i);

    return i;
}

StockChinaClose& StockChinaCloseArray::operator [](int i)
{
    return pStockChinaClose[i];
}

const StockChinaClose& StockChinaCloseArray::operator [](int i) const
{
    return pStockChinaClose[i];
}

const StockChinaCloseArray& StockChinaCloseArray::operator =(const StockChinaCloseArray& arr)
{
    if (size != arr.size)
    {
        if (pStockChinaClose != NULL)
        {
            delete[] pStockChinaClose;
            pStockChinaClose = NULL;
        }

        size = arr.size;
        if (size > 0)
        {
            pStockChinaClose = new StockChinaClose[size];
        }
    }

    if (pStockChinaClose != NULL)
        copyFrom(arr);

    return *this;
}


void StockChinaCloseArray::save(std::string filePath) const
{
    std::ofstream fileOUT(filePath, std::ios::out);
    for (size_t i = 0; i < size; i++)
    {
        fileOUT << pStockChinaClose[i].toString();
    }
    fileOUT.close();
}

void StockChinaCloseArray::copyFrom(const StockChinaCloseArray& arr)
{
    for (size_t i = 0; i < size; i++)
    {
        pStockChinaClose[i] = arr.pStockChinaClose[i];
    }
}

void StockChinaCloseArray::push_back(const StockChinaClose& st)
{
    resize(size + 1);
    pStockChinaClose[size - 1] = st;
}

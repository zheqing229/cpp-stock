#include "stockusarray.h"
#include "StockUS.h"

StockUSArray::StockUSArray(int size): StockArray(size), pStockUS(NULL)
{
    pStockUS = new StockUS [size];
}

StockUSArray::StockUSArray(const StockUSArray& arr): StockArray(arr.size), pStockUS(NULL)
{
    if (size <= 0) return;
    pStockUS = new StockUS[size];
    copyFrom(arr);
}

StockUSArray::~StockUSArray()
{
    if (pStockUS == NULL) return;

    delete[] pStockUS;
    pStockUS = NULL;
}

void StockUSArray::resize(int size, bool to_copy)
{
    if (this->size == size) return;
    ///////////////////////////////
    StockUS* pNew = NULL;
    if (size > 0)
    {//分配新空间；截取数据
        pNew = new StockUS[size];

        if (to_copy)//必要时才拷贝原始数据
        {
            int n = (size < this->size) ? size : this->size;
            for (int i = 0; i < n; i++)
            {
                pNew[i] = pStockUS[i];
            }
        }
    }

    this->size = size;
    if (pStockUS != NULL)
    {//释放原数据空间
        delete[] pStockUS;
        pStockUS = NULL;
    }

    pStockUS = pNew;
}


int StockUSArray::loadFrom(std::ifstream& fileIn)
{
    size_t i = 0;
    for (; !fileIn.eof() && (i < size); i++)
    {
        fileIn >> pStockUS[i];
        //std::cout << "Line_" << i << std::endl;
    }

    if (i < size) resize(i);

    return i;
}

StockUS& StockUSArray::operator [](int i)
{
    return pStockUS[i];
}

const StockUS& StockUSArray::operator [](int i) const
{
    return pStockUS[i];
}

const StockUSArray& StockUSArray::operator =(const StockUSArray& arr)
{
    if (size != arr.sizeOf())
    {
        if (pStockUS != NULL)
        {
            delete[] pStockUS;
            pStockUS = NULL;
        }

        size = arr.sizeOf();
        if (size > 0)
        {
            pStockUS = new StockUS[size];
        }
    }

    if (pStockUS != NULL)
        copyFrom(arr);

    return *this;
}

void StockUSArray::display() const
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << pStockUS[i].toString();
    }
}

void StockUSArray::save(std::string filePath) const
{
    std::ofstream fileOUT(filePath, std::ios::out);
    for (size_t i = 0; i < size; i++)
    {
        fileOUT << pStockUS[i].toString();
    }
    fileOUT.close();
}

void StockUSArray::copyFrom(const StockUSArray& arr)
{
    for (size_t i = 0; i < size; i++)
    {
        pStockUS[i] = arr.pStockUS[i];
    }
}

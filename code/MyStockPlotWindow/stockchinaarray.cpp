#include "stockchinaarray.h"


StockChinaArray::StockChinaArray(int size) :
    pStockChina(NULL)
{
    pStockChina = new StockChina[size];
}

StockChinaArray::StockChinaArray(const StockChinaArray& arr) :
    pStockChina(NULL)
{
    if (size <= 0) return;
    pStockChina = new StockChina[size];
    copyFrom(arr);
}

StockChinaArray::~StockChinaArray()
{
    if (pStockChina == NULL) return;

    delete[] pStockChina;
    pStockChina = NULL;
}

void StockChinaArray::resize(int size, bool to_copy)
{
    if (this->size == size) return;
    ///////////////////////////////
    StockChina* pNew = NULL;
    if (size > 0)
    {//分配新空间；截取数据
        pNew = new StockChina[size];

        if (to_copy)//必要时才拷贝原始数据
        {
            int n = (size < this->size) ? size : this->size;
            for (int i = 0; i < n; i++)
            {
                pNew[i] = pStockChina[i];
            }
        }
    }

    this->size = size;
    if (pStockChina != NULL)
    {//释放原数据空间
        delete[] pStockChina;
        pStockChina = NULL;
    }

    pStockChina = pNew;
}

int StockChinaArray::loadFrom(std::ifstream& fileIn, int s)
{
    size = s;
    resize(size);
    size_t i = 0;
    for (; !fileIn.eof() && (i < size); i++)
    {
        fileIn >> pStockChina[i];
        //std::cout << "Line_" << i << std::endl;
    }

    if (i < size) resize(i);

    return i;
}

StockChina& StockChinaArray::operator [](int i)
{
    return pStockChina[i];
}

const StockChina& StockChinaArray::operator [](int i) const
{
    return pStockChina[i];
}

const StockChinaArray& StockChinaArray::operator =(const StockChinaArray& arr)
{
    if (size != arr.size)
    {
        if (pStockChina != NULL)
        {
            delete[] pStockChina;
            pStockChina = NULL;
        }

        size = arr.size;
        if (size > 0)
        {
            pStockChina = new StockChina[size];
        }
    }

    if (pStockChina != NULL)
        copyFrom(arr);

    return *this;
}


void StockChinaArray::save(std::string filePath) const
{
    std::ofstream fileOUT(filePath, std::ios::out);
    for (size_t i = 0; i < size; i++)
    {
        fileOUT << pStockChina[i].toString();
    }
    fileOUT.close();
}

void StockChinaArray::copyFrom(const StockChinaArray& arr)
{
    for (size_t i = 0; i < size; i++)
    {
        pStockChina[i] = arr.pStockChina[i];
    }
}

void StockChinaArray::push_back(const StockChina& st)
{
    resize(size + 1);
    pStockChina[size - 1] = st;
}

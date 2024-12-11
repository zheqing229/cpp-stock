#include "indexstockarray.h"
#include "util.h"
#include "QDebug"

IndexStockArray::IndexStockArray() :
    pIndexStock(NULL), size(0)
{

}


IndexStockArray::IndexStockArray(const IndexStockArray& iarr):
    pIndexStock(NULL), size(iarr.size)
{
    pIndexStock = new IndexStock[iarr.size];
    copyfrom(iarr);
}

IndexStockArray::~IndexStockArray()
{
    if (pIndexStock == NULL) return;

    delete[] pIndexStock;
    pIndexStock = NULL;
}

void IndexStockArray::resize(int size, bool to_copy)
{
    if (this->size == size) return;
    ///////////////////////////////
    IndexStock* pNew = NULL;
    if (size > 0)
    {//分配新空间；截取数据
        pNew = new IndexStock[size];

        if (to_copy)//必要时才拷贝原始数据
        {
            int n = (size < this->size) ? size : this->size;
            for (int i = 0; i < n; i++)
            {
                pNew[i] = pIndexStock[i];
            }
        }
    }

    this->size = size;
    if (pIndexStock != NULL)
    {//释放原数据空间
        delete[] pIndexStock;
        pIndexStock = NULL;
    }

    pIndexStock = pNew;
}

void IndexStockArray::copyfrom(const IndexStockArray& iarr, bool toCopy)
{
    if (size != iarr.size)
        resize(iarr.size);
    if (toCopy) //默认复制值
    {
        for (int i = 0; i < iarr.size; i++)
        {
            pIndexStock[i] = iarr.pIndexStock[i];
        }
    }
}

IndexStock& IndexStockArray::operator[](int i)
{
    return pIndexStock[i];
}

const IndexStock& IndexStockArray::operator[](int i) const
{
    return pIndexStock[i];
}

void IndexStockArray::loadFrom(std::string filePath)
{
    std::ifstream filePathIn;
    filePathIn.open(filePath, std::ios::in | std::ios::binary);
    std::string titleline;
    int n = Util::lineNumberInFile(filePathIn, titleline, false);

    resize(n);

    int i = 0;
    for (i = 0; i < n; i++)
    {
        filePathIn  >> pIndexStock[i];
        //qDebug() << i << '\n';
    }
}

const IndexStockArray& IndexStockArray::operator =(const IndexStockArray& arr)
{
    if (size != arr.size)
    {
        if (pIndexStock != NULL)
        {
            delete[] pIndexStock;
            pIndexStock = NULL;
        }

        size = arr.size;
        if (size > 0)
        {
            pIndexStock = new IndexStock[size];
        }
    }

        if (pIndexStock != NULL)
            copyfrom(arr);

        return *this;
}

void IndexStockArray::push_back(const IndexStock& is)
{
    resize(size + 1);
    pIndexStock[size - 1] = is;
}

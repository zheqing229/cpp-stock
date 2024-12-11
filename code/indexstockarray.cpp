#include "indexstockarray.h"
#include "util.h"
#include "QDebug"

IndexStockArray::IndexStockArray() :
    StockArray(0), pIndexStock(NULL), filePathIn(""), filePathOut("")
{

}

IndexStockArray::IndexStockArray(std::string filepath):
    StockArray(2), pIndexStock(NULL), filePathIn(filepath), filePathOut("")
{
    pIndexStock = new IndexStock [2];
}

IndexStockArray::IndexStockArray(const IndexStockArray& iarr):
    StockArray(iarr.size), pIndexStock(NULL),
    filePathIn(iarr.filePathIn), filePathOut(iarr.filePathOut)
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

void IndexStockArray::resize(int newSize)
{
    delete[] pIndexStock;
    pIndexStock = NULL;
    pIndexStock = new IndexStock[newSize];
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

void IndexStockArray::setFilePathIn(std::string str)
{
    filePathIn = str;
}

std::string IndexStockArray::getFilePathIn() const
{
    return filePathIn;
}

void IndexStockArray::setFilePathOut(std::string str)
{
    filePathOut = str;
}

std::string IndexStockArray::getFilePathOut() const
{
    return filePathOut;
}

void IndexStockArray::setHaseTitle(bool ht)
{
    haseTitle = ht;
}

bool IndexStockArray::getHaseTitle() const
{
    return haseTitle;
}

///////////////////////////////////////////////////////////
///开辟两个空间，先读入pIndexStockArray[0]，然后继续读入下一行数据并存储在pIndexStockArray[1]，
/// 与pIndedxStockArray[0]进行比较，如果相同就继续，否则把pIndexStockArray[0]写入文件，
/// 并更新pIndexStockArray[0]的值。
/// （运算符==是Stock类里的，但是重载sym()函数返回月份信息使得可以延续使用。）
/// //////////////////////////////////////////////////////
void IndexStockArray::run()
{
    in.open(filePathIn, std::ios::in | std::ios::binary);
    out.open(filePathOut, std::ios::out);

    if (!in.is_open())  return;

    std::string title;
    int capacity = Util::lineNumberInFile(in, title, haseTitle);
    //qDebug() << capacity << '\n';

    in >> pIndexStock[0];
    out << pIndexStock[0].toString();

    for (int i = 0; i < capacity - 1; i++)
    {
        in >> pIndexStock[1];
        if (pIndexStock[0] == pIndexStock[1]) continue;

        out << pIndexStock[1].toString();
        pIndexStock[0] = pIndexStock[1];
        //qDebug() << i << '\n';
    }
    //qDebug() << "Done!" << '\n';
    in.close();
    out.close();
}

#ifndef BIGDATA_H
#define BIGDATA_H
#include <fstream>
#include <string>
#include "heap.h"
#include "mergesort.h"
#include "datadef.h"
#include "util.h"
// #include <QDebug>

template<class T1, class T2>
class BigData
{
private:
    std::string baseDirec;
    std::string bDataFile;
    size_t tableSize;
    size_t capacity;
    std::string titleLine;
    int smallFileCount; //分割后的小文件数
public:
    BigData(const std::string& dir = "D:\\");
    ~BigData();

    size_t externalSort(const std::string& fileName, bool haseTitleLine = true);

    //打开关闭文件
    size_t open(bool haseTitleLine = true);
    size_t open(const char* fileName, bool haseTitleLine = true);
    size_t open(const std::string& fileName, bool haseTitleLine = true);
    void close();

    //按文件(tableSize)大小分割
    void splitToSortedFiles(ORDER otype = ASC);
    //指定分割文件个数
    void splitToSortedFiles(int fileCount, ORDER otype = ASC);
    //合并已排序的小文件
    void mergeSortedFiles();
    void mergeSortedFiles(int fileCount, ORDER otype = ASC);
    //文件目录
    const std::string& getDir() const;
    void setDir(const std::string& newDir);

    //大文件名
    const std::string& getBDataFile() const;
    void setBDataFile(const std::string& newBDataFile);
    //用于加载小文件的内存数据表
    size_t getTableSize() const;
    void setTableSize(size_t newTableSize);
    int getSmallFileCount() const;
    void setSmallFileCount(int newSmallFileCount);

    ORDER getOrderType() const;
    void setOrderType(ORDER otype);

private:
    std::ifstream bigDataIn;
    std::ifstream* smallFileIns;
    std::ofstream bigDataOut;
    //内存数据结构
    T1 dTable;
    T1 heapT1;
    //排序工具类
    MergeSort<T1> mergSort;
    Heap<T1, T2> myheap;

private:
    int openSmallFiles(int count);
    int closeAllFiles();
};



template<class T1, class T2>
BigData<T1, T2>::BigData(const std::string& dir) :
    bDataFile(""),
    tableSize(1000),
    capacity(0),
    titleLine(""),
    smallFileCount(10),
    smallFileIns(NULL),
    dTable(T1(tableSize)),
    heapT1(T1(smallFileCount)),
    mergSort(MergeSort<T1>(dTable)),
    myheap(Heap<T1, T2>(heapT1))
{
    setDir(dir); //有针对常见使用习惯的容错设计
}

template<class T1, class T2>
BigData<T1, T2>::~BigData()
{
    closeAllFiles();

    if (smallFileIns != NULL)
    {
        delete[] smallFileIns;
    }

}

//////////
/// \brief BigData::externalSort
/// 按默认设置的升序和小文件数，对大文件数据进行外排。执行前，也可通重新设置
/// 排序方式和小文件数。
/// \param fileName: 大数据源文件名
/// \param haseTitleLine: 数据是否有标题行
/// \return 大文件中的数据总行数（不含标题行）
///

template<class T1, class T2>
size_t BigData<T1, T2>::externalSort(const std::string& fileName, bool haseTitleLine)
{
    capacity = open(fileName, haseTitleLine);
    splitToSortedFiles(mergSort.getOrderType());
    mergeSortedFiles();
    return capacity;
}

template<class T1, class T2>
const std::string& BigData<T1, T2>::getDir() const
{
    return baseDirec;
}

template<class T1, class T2>
void BigData<T1, T2>::setDir(const std::string& newDir)
{
    baseDirec = newDir;
    int end = baseDirec.length() - 1;
    if (end < 1) return;
    if (baseDirec[end] != '\\') baseDirec += '\\';
}

template<class T1, class T2>
const std::string& BigData<T1, T2>::getBDataFile() const
{
    return bDataFile;
}

template<class T1, class T2>
void BigData<T1, T2>::setBDataFile(const std::string& newBDataFile)
{
    bDataFile = newBDataFile;
}

template<class T1, class T2>
size_t BigData<T1, T2>::getTableSize() const
{
    return tableSize;
}

template<class T1, class T2>
void BigData<T1, T2>::setTableSize(size_t newTableSize)
{
    tableSize = newTableSize;
}

template<class T1, class T2>
int BigData<T1, T2>::getSmallFileCount() const
{
    return smallFileCount;
}

template<class T1, class T2>
void BigData<T1, T2>::setSmallFileCount(int newSmallFileCount)
{
    smallFileCount = newSmallFileCount;
}

template<class T1, class T2>
ORDER BigData<T1, T2>::getOrderType() const
{
    return mergSort.getOrderType();
}

template<class T1, class T2>
void BigData<T1, T2>::setOrderType(ORDER otype)
{
    mergSort.setOrderType(otype);
}

template<class T1, class T2>
size_t BigData<T1, T2>::open(bool haseTitleLine)
{
    return open(bDataFile, haseTitleLine);
}

template<class T1, class T2>
size_t BigData<T1, T2>::open(const char* fileName, bool haseTitleLine)
{
    bDataFile = fileName;
    return open(bDataFile, haseTitleLine);
}

//以二进制方式打开文本文件，确保读取位置定位精准，能正确地随机读取
template<class T1, class T2>
size_t BigData<T1, T2>::open(const std::string& fileName, bool haseTitleLine)
{
    bigDataIn.open(fileName, std::ios::in | std::ios::binary);

    if (!bigDataIn.is_open())  return (capacity = 0);
    //setBDataFile(fileName); //文件名正确
    //总数据量(行数）
    capacity = Util::lineNumberInFile(bigDataIn, titleLine, haseTitleLine);

    return capacity;
}

template<class T1, class T2>
void BigData<T1, T2>::close()
{
    closeAllFiles();
}


template<class T1, class T2>
void BigData<T1, T2>::splitToSortedFiles(ORDER otype)
{
    mergSort.setOrderType(otype);

    int fileCount = capacity / tableSize;
    smallFileCount = fileCount;
    //重置内存数据空间的大小
    dTable.resize(tableSize, false);

    //小文件名_编号
    std::string subFile = baseDirec + "SortedSubDataFile_";

    for (int i = 0; i < (fileCount - 1); i++)
    {
        int n = dTable.loadFrom(bigDataIn);
        // qDebug() << i << '\n';
        mergSort.run();
        dTable.save(subFile + std::to_string(i) + ".csv");
    }

    if ((capacity % tableSize) < (tableSize / 2))
    {
        //剩余部分合并到最后一个文件
        dTable.resize(((capacity % tableSize) + tableSize), false);
        dTable.loadFrom(bigDataIn);
        mergSort.run();
        dTable.save(subFile + std::to_string(fileCount - 1) + ".csv");
    }
    else
    {
        dTable.loadFrom(bigDataIn);
        mergSort.run();
        dTable.save(subFile + std::to_string(fileCount - 1) + ".csv");

        //剩余部分超过额定小文件数据的一半，独立成一个小文件
        dTable.resize((capacity % tableSize), false);
        dTable.loadFrom(bigDataIn);
        mergSort.run();
        dTable.save(subFile + std::to_string(fileCount) + ".csv");

        smallFileCount++;
    }
}


template<class T1, class T2>
void BigData<T1, T2>::splitToSortedFiles(int fileCount, ORDER otype)
{
    if (fileCount <= 0) return;
    mergSort.setOrderType(otype);

    smallFileCount = fileCount;
    //小文件数据行数，即内存数据表的额定大小，它是决定大数据文件处理
    //内存空间消耗的关键因素
    tableSize = capacity / fileCount;
    dTable.resize(tableSize, false); //加载数据前扩展内存空间

    std::string subFile = baseDirec + "SortedSubDataFile_";
    for (int i = 0; i < (fileCount - 1); i++)
    {
        dTable.loadFrom(bigDataIn);
        // qDebug() << i << '\n';
        mergSort.run(); //排序
        dTable.save(subFile + std::to_string(i) + ".csv"); //保存
    }
    //可能残余的数据（少于fileCount行）加载到最后一个小文件中
    dTable.resize(((capacity % fileCount) + tableSize), false);
    dTable.loadFrom(bigDataIn);
    mergSort.run();
    dTable.save(subFile + std::to_string(fileCount - 1) + ".csv");
}

template<class T1, class T2>
void BigData<T1, T2>::mergeSortedFiles()
{
    //打开已排序的小文件
    if (openSmallFiles(smallFileCount) == 0) return;
    //打开（新建）合并的有序大文件
    std::string otype = "ASCSorted_";
    if (mergSort.getOrderType() == DES) otype = "DESSorted_";
    bigDataOut.open((baseDirec + otype + bDataFile), std::ios::out | std::ios::binary);

    if (titleLine.length() > 0) bigDataOut << titleLine << '\n'; //写入标题行

    int srcFileId = 0, count = 0; //已合并结束的小文件数
    ////////////////开始合并/////////////////////
    T2& heapTop = myheap.getHeapTop(); //堆顶节点
    while (true)
    {
        srcFileId = heapTop.getSrcID();
        //正常读取的数据，保存到合并文件。
        if (smallFileIns[srcFileId].good())
        {
            bigDataOut << heapTop;
        }
        //文件尾有空换行符时，会读取异常然后才到 eof状态
        if (!smallFileIns[srcFileId].eof())
        {
            //读取数据，更新已保存的堆顶节点
            smallFileIns[srcFileId] >> heapTop;
            //维持堆的有效性
            myheap.heapify(0);
        }
        else //↓↓↓ 节点绑定文件已没有数据，从堆上移除
        {
            //qDebug() << "FILE_" << srcFileId << " has been fully merged." << '\n';
            if ((++count) == smallFileCount) break;
            //交换堆顶，缩小堆,并维持堆的有效性; 相应
            myheap.downSize(); //小文件的节点被排除
        }
    }
    ////////////////合并结束/////////////////////
}

//若已有排好序的若干小文件（命名_编号规则一致）
template<class T1, class T2>
void BigData<T1, T2>::mergeSortedFiles(int fileCount, ORDER otype)
{
    smallFileCount = fileCount;
    mergSort.setOrderType(otype);
    mergeSortedFiles();
}


//打开已排序小文件，并准备堆所需的初始数据：
template<class T1, class T2>
int BigData<T1, T2>::openSmallFiles(int count)
{
    smallFileIns = new std::ifstream[count];

    std::string subFile = baseDirec + "SortedSubDataFile_";
    T1 arr(count);
    int n = 0;
    for (int i = 0, j = 0; i < count; i++)
    {
        //二进制，只读方式打开
        smallFileIns[i].open(subFile + std::to_string(i) + ".csv",
            std::ios::in | std::ios::binary);

        if (smallFileIns[i].is_open())//检查是否成功打开
        {
            smallFileIns[i] >> arr[j]; //
            arr[j].setSrcID(i); //标记（绑定）堆上节点的数据来源
            j++, n++;
        }
    }

    if (n < count)
        arr.resize(n);

    //初始化堆, 因分割的小文件数往往不是创建堆时它的节点数

    heapT1 = arr;
    if (mergSort.getOrderType() == DES)
    {
        myheap.setHeapType(MAX);
    }
    else
    {
        myheap.setHeapType(MIN);
    }

    myheap.initialize();

    return n;
}

//关闭所有文件
template<class T1, class T2>
int BigData<T1, T2>::closeAllFiles()
{
    int n = 0;
    if (bigDataIn.is_open())
    {
        bigDataIn.close();
        n++;
    }

    if (bigDataOut.is_open())
    {
        bigDataOut.close();
        n++;
    }

    //所有可能打开的小文件
    for (int i = 0; (smallFileIns != NULL) && (i < smallFileCount); i++)
    {
        if (smallFileIns[i].is_open())
        {
            smallFileIns[i].close();
            n++;
        }
    }
    return n;
}


#endif // BIGDATA_H

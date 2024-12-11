#include "bigdata.h"
#include "stockchinaarray.h"
#include "stockusarray.h"
#include "indexstockarray.h"

int main()
{

//    BigData<StockChinaArray, StockChina> bdCh("D:\\stock\\sorted\\");//类模板实例化
//    size_t n = bdCh.open("D:\\stock\\stock_china_20220325.csv"); //指定数据文件名
//    bdCh.splitToSortedFiles(110);//指定排序小文件个数
//    //bdCh.setOrderType(DES); 可改变排序方式
//    bdCh.setBDataFile("output_China.csv");
//    bdCh.mergeSortedFiles(); //数据总数
//    //qDebug() << n << "Stock China has been sorted" << '\n';

//    BigData<StockUSArray, StockUS> bdUS("D:\\stock_data\\BDUS\\");//类模板实例化
//    bdUS.setTableSize(20000);//指定单个排序小文件内数据数量
//    //bdUS.setOrderType(DES); //可改变排序方式
//    bdUS.setBDataFile("output_US.csv");
//    size_t m = bdUS.externalSort("D:\\stock_data\\part_us_stock_daily_random.csv");//指定数据文件名
//    qDebug() << m << "Stock US has been sorted." << '\n'; //数据总数


    IndexStockArray arr("D:\\stock\\sorted\\ASCSorted_output_China.csv");
    //创建索引向量输入文件路径
    arr.setFilePathOut("D:\\stock\\index.csv");//设置输出文件路径
    arr.setHaseTitle(true);
    arr.run();
}

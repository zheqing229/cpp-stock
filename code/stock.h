#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Stock
{
public:
    Stock(int sid = 0) :SrcID(sid) {}
    virtual ~Stock();

    virtual const Stock& operator=(const Stock& st) = 0;

    //节点的字符串形式
    virtual std::string toString() const = 0;

    //获得节点的特征值, 主要用于关系比较；可用多个字段按一定规则计算组合而成。
    virtual std::string sym() const = 0;
    virtual std::string dt() const = 0;

    bool operator >(const Stock& st) const;
    bool operator >=(const Stock& st) const;
    bool operator ==(const Stock& st) const;
    bool operator <=(const Stock& st) const;
    bool operator <(const Stock& st) const;

    int getSrcID() const;
    void setSrcID(int newSrcID);

    //友元函数，文件流输入输出
    friend std::ifstream& operator >> (std::ifstream& in,
        Stock& st);
    friend std::ofstream& operator << (std::ofstream& out,
        const Stock& st);


private:
    //从文件流中读入【当前行】数据到节点中
    virtual void readline(std::ifstream& in) = 0;
    //将节点数据写入文件
    virtual void write(std::ofstream& out) const = 0;


protected:
    int SrcID;
};

inline int Stock::getSrcID() const
{
    return SrcID;
}

inline void Stock::setSrcID(int newSrcID)
{
    SrcID = newSrcID;
}

#endif // STOCK_H

#ifndef LINEARPROGRAMMING_H
#define LINEARPROGRAMMING_H

#include <QVector>

class LinearProgramming
{//y_pred = b * x + a
public:
    LinearProgramming();

    double Average(QVector<double> v);//计算平均值
    void calculate(QVector<double>x, QVector<double> y);//计算a和b
    double predict(double x);//预测计算y=b*x+a

private:
    double a;
    double b;

};

#endif // LINEARPROGRAMMING_H

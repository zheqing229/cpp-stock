#include "linearprogramming.h"

LinearProgramming::LinearProgramming()
{

}

double LinearProgramming::Average(QVector<double> v)
{
    double sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }
    return sum / v.size();
}

void LinearProgramming::calculate(QVector<double> x, QVector<double> y)
{
    double sum_x_y = 0;//(yi-y_aver)(xi-x_aver)
    double sum_X = 0; //(xi-x_aver)**2
    double x_aver = Average(x);
    double y_aver = Average(y);
    for(int i = 0; i < x.size(); i++)
    {
        sum_x_y += (x[i] - x_aver) * (y[i] - y_aver);
        sum_X += (x[i] - x_aver) * (x[i] - x_aver);
    }
    b = sum_x_y / sum_X;
    a = y_aver - b * x_aver;
}

double LinearProgramming::predict(double x)
{
    double y_pred;
    y_pred = b * x + a;
    return y_pred;
}

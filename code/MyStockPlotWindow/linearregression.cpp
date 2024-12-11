#include "linearregression.h"
#include "qdebug.h"

LinearRegression::LinearRegression():learning_rate(0), max_iter(0), w(0), b(0)
{
}

LinearRegression::LinearRegression(double lr, int max_i)
    :learning_rate(lr), max_iter(max_i), w(0), b(0)
{
    std::srand((int)time(0));
    w = (std::rand() % 10) / 10.0;
    b = (std::rand() % 10) / 10.0;
}

QVector<double> LinearRegression::fit(QVector<double> x, QVector<double> y)
{
    QVector<double> y_pred;
    for (int i = 0; i < max_iter; i++)
    {
        train_step(x, y);
        y_pred = predict(x);
        loss_arr.push_back(loss(y, y_pred));
    }
    for (int i = 0; i < loss_arr.size(); i++)
        qDebug() << "loss" << i << ' ' << loss_arr[i] << '\n';
    return y_pred;
}

QVector<double> LinearRegression::predict(QVector<double> x)
{
    QVector<double> y_pred;
    for (int i = 0; i < x.size(); i++)
        y_pred.push_back(x[i] * w + b);
    return y_pred;
}

double LinearRegression::loss(QVector<double> y, QVector<double> y_pred)
{
    double sum = 0;
    double mse = 0;
    for (int i = 0; i < y.size(); i++)
        sum += (y[i] - y_pred[i]) * (y[i] - y_pred[i]);
    mse = sum / y.size();
    return std::sqrt(mse);
}

double* LinearRegression::__calc_gradient(QVector<double> x, QVector<double> y)
{
    double* dw_and_db;
    dw_and_db = new double[2];
    double sum_w = 0, sum_b = 0;
    for (int i = 0; i < x.size(); i++)
    {
        double temp = 2 * (x[i] * w + b - y[i]);
        sum_w += temp * x[i];
        sum_b += temp;
    }
    dw_and_db[0] = (sqrt(sum_w / x.size()) > 0.000001) ? sqrt(sum_w / x.size()) : 0;
    dw_and_db[1] = (sqrt(sum_b / x.size()) > 0.000001) ? sqrt(sum_b / x.size()) : 0;
    ///如果小于0.000001相当于梯度每下降，防止数字过小使double不能显示而返回nan
    return dw_and_db;//返回w和b的梯度，因为是两个值，设计成返回数组指针
}

void LinearRegression::train_step(QVector<double> x, QVector<double> y)
{
    double* dw_and_db = __calc_gradient(x, y);
    double d_w = dw_and_db[0];
    double d_b = dw_and_db[1];
    delete[] dw_and_db;
    w -= learning_rate * d_w;
    b -= learning_rate * d_b;
}


///初始化
void LinearRegression::initialize()
{
    std::srand((int)time(0));//随机
    w = (std::rand() % 10);
    b = (std::rand() % 10);
}

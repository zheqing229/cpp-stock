#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <QVector>
#include <cstdlib>
#include <ctime>
#include <cmath>
class LinearRegression
{
public:
    LinearRegression();
    LinearRegression(double lr, int max_i);

    QVector<double> fit(QVector<double> x, QVector<double> y);//

    QVector<double> predict(QVector<double> x);//预测

    double loss(QVector<double> y, QVector<double> y_pred);//计算误差，损失函数

    double* __calc_gradient(QVector<double> x, QVector<double> y);//计算梯度（梯度下降法）

    void train_step(QVector<double> x, QVector<double> y);//训练

    void setLearningRate(double d) { learning_rate = d; }//设置学习率

    void setMaxIter(int i) { max_iter = i; }//设置迭代数

    double getW() { return w; }
    double getB() { return b; }

    void initialize();
private:
    double learning_rate;//学习率
    int max_iter;//迭代数
    QVector<double>  loss_arr;//损失
    double w;
    double b;
};

#endif // LINEARREGRESSION_H

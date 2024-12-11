#ifndef MERGESORT_H
#define MERGESORT_H

#include "datadef.h"

template <class T>
class MergeSort
{
    T& Arr;
    ORDER order_type;
   // const std::type_info& arrInfo;

public:
    //通过引用的方式，绑定要排序的动态数组
    MergeSort(T& stockArr, ORDER otype = ASC) : Arr(stockArr), order_type(otype)
    {
    }

    void run()
    {
        int start = 0;
        int end = Arr.sizeOf() - 1;
        mergeSort(start, end);
    }

    ORDER getOrderType() const { return order_type; }
    void setOrderType(ORDER newOrder_type) { order_type = newOrder_type; }


private:
    void merge(int start, int end)
    {
        int mid = (start + end) / 2;
        int leftSize = mid - start + 1;
        int rightSize = end - mid;

        T leftArr(leftSize);
        T rightArr(rightSize);

        for (int i = 0; i < leftSize; i++)
            leftArr[i] = Arr[start + i];
        for (int j = 0; j < rightSize; j++)
            rightArr[j] = Arr[mid + 1 + j];


        int i = 0;
        int j = 0;
        int k = start;

        while (i < leftSize && j < rightSize)
        {
            if ((order_type == ASC && leftArr[i] <= rightArr[j]) ||
                (order_type == DES && leftArr[i] >= rightArr[j]))
            {
                Arr[k] = leftArr[i];
                i++;
            }
            else
            {
                Arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < leftSize)
        {
            Arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < rightSize)
        {
            Arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    void mergeSort(int start, int end)
    {
        if (start < end)
        {
            int mid = (start + end) / 2;
            mergeSort(start, mid);
            mergeSort(mid + 1, end);
            merge(start, end);
        }
    }


};

#endif // MERGESORT_H

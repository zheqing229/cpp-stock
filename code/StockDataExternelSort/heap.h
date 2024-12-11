#ifndef HEAP_H
#define HEAP_H

#include "datadef.h"

template<class T1, class T2> // T1 array T2 single object
class Heap
{
private:
    T1& Arr; // 堆的数据源，引用
    int heap_size;
    HPTYPE heap_type;

    // 根据堆类型，返回i,j两位置中节点“值”较小或较大者
    inline int min_maxIdx(int i, int j);
    // 交换节点
    void swap(T2& x, T2& y);

public:
    // 创建指定大小的堆，默认为 MaxHeap 类型
    Heap(T1& Arr, HPTYPE ht = MAX);

    // 堆的大小或类型发生变化后，须重新初始化
    void initialize();

    // 在指定索引位置生成一个子树堆
    void heapify(int i = 0);
    // 获取父节点的索引位置
    int parent(int i) { return (i - 1) / 2; }
    // 获取给定位置的左子节点的索引位置
    int left(int i) { return (2 * i + 1); }
    // 获取给定位置的右子节点的索引位置
    int right(int i) { return (2 * i + 2); }

    // 获得堆顶（最大或最小）根节点。
    // Q: 节点返回的方式
    T2& getHeapTop() { return Arr[0]; }

    // 获取堆的大小
    int sizeOf() { return heap_size; }
    int downSize();

    HPTYPE getHeapType() const;
    void setHeapType(HPTYPE newHeap_type);

    int getSrcIdAt(int i = 0) const { return Arr[i].getSrcID(); }
};

template<class T1, class T2>
Heap<T1, T2>::Heap(T1& Arr, HPTYPE ht) : Arr(Arr), heap_size(Arr.sizeOf()), heap_type(ht)
{
}

template<class T1, class T2>
void Heap<T1, T2>::initialize()
{
    heap_size = Arr.sizeOf();

    int i = (heap_size - 1) / 2;
    for (; i >= 0; i--)
    {
        heapify(i);
    }
}

template<class T1, class T2>
void Heap<T1, T2>::heapify(int i)
{
    if (heap_size <= 1)
        return;

    int l = left(i);  // 左子节点
    int r = right(i); // 右子节点

    // 根据堆的类型，在i, l, r三个位置中，
    // 得到最小(MinHeap)或最大值的位置
    int idxMinMax = min_maxIdx(min_maxIdx(i, l), r);
    if (idxMinMax == i)
        return;

    swap(Arr[i], Arr[idxMinMax]);
    heapify(idxMinMax);
}

template<class T1, class T2>
int Heap<T1, T2>::downSize()
{
    swap(Arr[0], Arr[--heap_size]);
    heapify(0);
    return heap_size;
}

template<class T1, class T2>
HPTYPE Heap<T1, T2>::getHeapType() const
{
    return heap_type;
}

template<class T1, class T2>
void Heap<T1, T2>::setHeapType(HPTYPE newHeap_type)
{
    if (heap_type == newHeap_type)
        return;
    heap_type = newHeap_type;

    initialize();
}

template<class T1, class T2>
void Heap<T1, T2>::swap(T2& x, T2& y)
{
    T2 tmpT2 = x;
    x = y;
    y = tmpT2;
}

template<class T1, class T2>
inline int Heap<T1, T2>::min_maxIdx(int i, int j)
{
    if (i >= heap_size)
        return heap_size - 1;
    if (j >= heap_size)
        return i;

    // TODO:
    if (((heap_type == MIN) && (Arr[j] < Arr[i])) ||
        ((heap_type == MAX) && (Arr[j] > Arr[i])))
    {
        return j;
    }

    return i;
}


#endif // !HEAP_H


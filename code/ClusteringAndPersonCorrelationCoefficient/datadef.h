#ifndef MYDATADEF_H
#define MYDATADEF_H

//ASC 升序：ascending order	0
//DES 降序：descending order 1
enum ORDER { ASC, DES };

//MAX: MaxHeap 0
//MIN: MinHeap 1
enum HPTYPE { MAX, MIN };


const long long _NaN = 0xFFF8000000000000;
const long long _InfLL = 0x7FF0000000000000;
const long long _NegInfLL = 0xFFF0000000000000;

//double
const double NaN = *((double*)&_NaN);
const double Inf = *((double*)&_InfLL);
const double NegInf = *((double*)&_NegInfLL);
#endif // MYDATADEF_H

#ifndef BIGINT_H
#define BIGINT_H

#include<cmath>
#include<Qstring>
typedef qlonglong qllong;
#define MAXN 5000
#define BASE 100000000                  //采用10^8进制
#define BASELEN 8
class BigInt
{
    bool sign;                          //0表示正，1表示负
    qllong  digital[MAXN];
    int len;                            //当前大整数的长度
public:
    //构造函数
    BigInt();
    BigInt(qllong );
    BigInt(const BigInt &);
    //赋值号重载：
    BigInt& operator =(const BigInt &);
    BigInt& operator = (QString);

    //二目运算符：
    BigInt operator +(const BigInt &);
    BigInt operator -(const BigInt &);
    BigInt operator *(const BigInt &);
    BigInt operator /(const BigInt &);
    BigInt operator +(int n);
    BigInt operator -(int n);
    BigInt operator *(int n);
    BigInt operator /(int n);
    bool operator >(const BigInt &);
    bool operator <(const BigInt &);
    BigInt& operator +=(const BigInt &);
    BigInt& operator -=(const BigInt &);
    BigInt& operator *=(const BigInt &);
    BigInt operator ^(int n);               //大整数乘方
    BigInt operator %(BigInt);              //大整数求模
    BigInt& operator >>=(int n);            //大整数在二进制上右移n位
    BigInt& operator <<=(int n);            //大整数在二进制上右移n位

    //一些函数：
    bool Zero()const;                       //判断大整数是否为零
    qllong FirSecDigit();                    //返回前两位元素
    BigInt Sqrt();                          //求大整数的平方根
    void Factorial(int n);                  //求阶乘
    void Factorial(int n,char c);           //求双阶乘
    BigInt Shift(int n);                    //十进制移位
    int Cmp(const BigInt &,bool Is_Abs=0);  //比较函数,第二个参数为1则表示绝对值比较，默认比较本身大小
friend void Swap(BigInt *num1,BigInt *num2);//交换两个大整数
    QString toQString();                    //转换为字符串

    bool isLegal;
};

#endif // BIGINT_H

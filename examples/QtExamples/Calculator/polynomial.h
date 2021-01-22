#ifndef POLYNOMIAL_HH
#define POLYNOMIAL_HH
#include"Complex.h"
class Polynomial
{
	int n;
	Complex *p;
public:
    Polynomial(){}
	Polynomial(int nn,Complex *a);
    Polynomial(const Polynomial &poly);
    Polynomial & operator =(Polynomial Obj);
	 ~Polynomial(){delete [] p;}
    Complex poly_value(const Complex &x);           //多项式求值
    void poly_reduce(const Complex &root);          //多项式降阶
    double poly_search_R();
	double fitness(Complex x);
    int getOrder(){return n;}
    void setOrder(int n){this->n=n;}
    Complex getRatio(int index){return p[index];}
};
#endif

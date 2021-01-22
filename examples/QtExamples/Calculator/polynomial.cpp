#include"Polynomial.h"
#include<cmath>
Polynomial::Polynomial(int nn,Complex *a)
{
	n=nn;
	p= new Complex [n+1];
	for(int i=0;i<=n;i++)
		p[i] = a[i];
}
Polynomial::Polynomial(const Polynomial &poly)
{
    n=poly.n;
    p= new Complex[n+1];
    for(int i=0;i<=n;i++)
        p[i] = poly.p[i];
}
Polynomial & Polynomial::operator = (Polynomial Obj)
{
    n=Obj.n;
    p= new Complex[n+1];
    for(int i=0;i<=n;i++)
        p[i] = Obj.p[i];
    return *this;
}
Complex Polynomial::poly_value(const Complex &x)   //多项式求值p(x)
{
	Complex value;
	value = p[0];
	for(int k=1; k<=n; k++)  
		value = value*x + p[k];
	return value;
}		   
void Polynomial::poly_reduce(const Complex &root)
{
    for(int i=1;i<n;++i)
    {p[i]+=p[i-1]*root;}
    n--;
}
double Polynomial::poly_search_R()
{
    double R=p[1].cfabs();
    for(int i=2;i<=n;i++)
	{
        if(p[i].cfabs()>R)
            R=p[i].cfabs();
	}
    R=R+1;
    for(int i=0;i<=n;i++)
    {
        p[i]*=pow(R,n-i);
    }
    return R;
}
double Polynomial::fitness(Complex x)
{
    return 1/(1+poly_value(x).cfabs());
}

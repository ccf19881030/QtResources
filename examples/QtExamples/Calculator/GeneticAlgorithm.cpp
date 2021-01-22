#include"GeneticAlgorithm.h"
#include<ctime>
#include<cstdlib>
GeneticAlgorithm::GeneticAlgorithm(const Polynomial &p)
{
    poly = p;
    originalPoly = p;
    e=0.999;
}
unit GeneticAlgorithm::encode(double real,double imag)
{
    unit new_u;
    if(real<0){
        new_u.x[0]=1;
        real=-real;
    }else
        new_u.x[0]=0;
    if(imag<0){
        new_u.x[1]=1;
        imag=-imag;
    }else
        new_u.x[1]=0;

    for(int i=2;i<20;i+=2)
    {
        real*=10;
        new_u.x[i]=int(real);
        real-=int(real);
    }
    for(int i=3;i<20;i+=2)
    {
        imag*=10;
        new_u.x[i]=int(imag);
        imag-=int(imag);
    }
    return new_u;
}
Complex GeneticAlgorithm::decode(const unit &u1)
{
    double real=0.0,imag=0.0;
    double temp=1.0;
    for(int i=2;i<20;i+=2){
        temp*=0.1;
        real+=(u1.x[i]*temp);
    }
    temp=1.0;
    for(int i=3;i<20;i+=2){
        temp*=0.1;
        imag+=(u1.x[i]*temp);
    }
    if(u1.x[0]==1)
        real=-real;
    if(u1.x[1]==1)
        imag=-imag;
    if(qAbs(real)<1e-5)
        real=0;
    if(qAbs(imag)<1e-5)
        imag=0;
    return Complex(real,imag);
}
unit GeneticAlgorithm::crossover(unit &u1, unit &u2)
{
    unit new_u;
    for(int i=0;i<6;i++)
    {
        new_u.x[i]=u1.x[i];
    }
    for(int i=6;i<20;i++)
    {
        new_u.x[i]=(u1.x[i]+u2.x[i])/2;
    }
    return new_u;
}
unit GeneticAlgorithm::variation01(const unit &u1,double pm1,double pm2)
{
    unit new_u;
    int i;
    double ni;
    new_u.x[0]=u1.x[0];
    new_u.x[1]=u1.x[1];
    for(i=2;i<6;i++)
    {
        ni=rand()/(RAND_MAX+0.0);
        if(ni<pm1)
        {
            if(u1.x[i]>0&&u1.x[i]<9)
                new_u.x[i]=rand()%2?(u1.x[i]+1):(u1.x[i]-1);
            else if(u1.x[i]==0)
                new_u.x[i]=1;
            else
                new_u.x[i]=8;
        }
        else
            new_u.x[i]=u1.x[i];
    }
    for(i=6;i<20;i++)
    {
        ni=rand()/(RAND_MAX+0.0);
        if(ni<pm2)
        {
            new_u.x[i]=rand()%10;
        }
        else
            new_u.x[i]=u1.x[i];
    }
    new_u.fitness=poly.fitness(decode(new_u));
    return new_u;
}
unit GeneticAlgorithm::variation02(const unit &u1)
{
    unit new_u;
    int i;
    double ni;
    for(i=0;i<6;i++)
        new_u.x[i]=u1.x[i];
    for(i=6;i<10;i++){
        ni=rand()/(RAND_MAX+0.0);
        if(ni<0.1)
        {
            if(u1.x[i]>0&&u1.x[i]<9){
                new_u.x[i]=rand()%2?(u1.x[i]+1):(u1.x[i]-1);
                continue;
            }
            if(u1.x[i]==0)
                new_u.x[i]=1;
            else
                new_u.x[i]=8;
        }
        else
            new_u.x[i]=u1.x[i];
    }
    new_u.x[rand()%10+10]=rand()%10;
    new_u.x[rand()%10+10]=rand()%10;
    new_u.fitness=poly.fitness(decode(new_u));
    return new_u;
}
void GeneticAlgorithm::initialize()
{
    int i,j,m,n,count=0;
    Complex num1,num2,num3,num4;
    double temp1,temp2,temp3;
    double real,imag;
    double fit,pm=0.4;
    bool work = false;
    for(i=0;i<u;i++)
    {
        for(j=6;j<20;j++)
            group[i].x[j]=0;
    }
START:for(i=0;i<10;++i)
    {
        temp1=0.1*i;
        for(j=0;j<10;++j)
        {
            temp2=0.1*j;
            for(m=0;m<10;++m)
            {
                temp3=0.01*m;
                for(n=0;n<10;++n)
                {
                    real=temp1+temp3,imag=temp2+0.01*n;
                    num1=Complex(real,imag);
                    num2=Complex(real,-imag);
                    num3=Complex(-real,imag);
                    num4=Complex(-real,-imag);
                    if(count>=100){
                        work=true;goto END;
                    }
                    if((fit=poly.fitness(num1))>pm)
                    {
                        group[count].x[0]=0;
                        group[count].x[1]=0;
                        group[count].x[2]=i;
                        group[count].x[3]=j;
                        group[count].x[4]=m;
                        group[count].x[5]=n;
                        group[count].fitness=fit;
                        count++;
                    }
                    if((fit=poly.fitness(num2))>pm)
                    {
                        group[count].x[0]=0;
                        group[count].x[1]=1;
                        group[count].x[2]=i;
                        group[count].x[3]=j;
                        group[count].x[4]=m;
                        group[count].x[5]=n;
                        group[count].fitness=fit;
                        count++;
                    }
                    if((fit=poly.fitness(num3))>pm)
                    {
                        group[count].x[0]=1;
                        group[count].x[1]=0;
                        group[count].x[2]=i;
                        group[count].x[3]=j;
                        group[count].x[4]=m;
                        group[count].x[5]=n;
                        group[count].fitness=fit;
                        count++;
                    }
                    if((fit=poly.fitness(num4))>pm)
                    {
                        group[count].x[0]=1;
                        group[count].x[1]=1;
                        group[count].x[2]=i;
                        group[count].x[3]=j;
                        group[count].x[4]=m;
                        group[count].x[5]=n;
                        group[count].fitness=fit;
                        count++;
                    }
                }
            }
        }
    }
END:  if(work==false){
        if(count<=10)
            {pm/=2;goto START;}
      for(i=count;i<u;i++)
          group[i]=variation01(group[i%count],0.1,0.5);
      }
}
bool GeneticAlgorithm::searchRoot(Complex *roots)
{
    int n=poly.getOrder(),i,count=0;
    double S[v+1],fitmax=0,fitsum=0,temp;
    unit newGroup[v];
    srand(unsigned(time(NULL)));
    double R=poly.poly_search_R();   //将多项式的解的绝对值缩到(0,1)
    for(i=n;i>=0;--i)//求出根为零的情况
    {
        if(!poly.getRatio(i).isZero())
        {
            for(count=0;count<n-i;count++)
            {roots[count]=0;}
            n=i;
            poly.setOrder(n);
            break;
        }
    }
    while(n>1)
    {
        initialize();        //初始化群体
        int best=0,g=0;
        //求阶数为n的一个根
        while(g++<nga)       //nga=1000，表示最大进化代数
        {
            //u==100,v==200
            for(i=0;i<u;i++)     //将就个体复制到新个体中
                newGroup[i]=group[i];
            if(fitmax<=0.98)
                for(i=u;i<v;i++)   //对重组后的个体进行突变, 产生新个体.
                {
                    newGroup[i]=variation01(newGroup[i-u],0.1,0.2);
                }
            else
                for(i=u;i<v;i++)   //对重组后的个体进行突变, 产生新个体.
                {
                    newGroup[i]=variation02(newGroup[i-u]);
                }
            fitsum=fitmax=newGroup[0].fitness;
            best =0;
            for(i=1;i<v;i++)   //找最大适应度
            {
                temp=newGroup[i].fitness;
                fitsum+=temp;
                if(temp>fitmax){
                    fitmax=temp;
                    best=i;
                }
            }

            if(fitmax>=e)              //终止条件,e=0.999999
                break;
            for(i=0,S[0]=0.0;i<v;i++)  //轮盘赌选择方式(比例选择)
            {
                S[i+1]=S[i]+newGroup[i].fitness/fitsum;
            }
            group[0]=newGroup[best];
            for(i=1;i<u;i++)           //挑选优良个体组成一代群体,一共u个
            {
                temp=rand()/(RAND_MAX+0.0);
                int low=0,high=v,mid;
                while(low<=high)
                {
                    mid = (low+high)/2;
                    if(S[mid]<temp)
                        low=mid+1;
                    else if(S[mid]>temp)
                        high=mid-1;
                    else
                        break;
                }
                mid=(low+high)/2;
                group[i]=newGroup[mid];
            }
        }
        roots[count]=decode(newGroup[best]); //将结果解码
        poly.poly_reduce(roots[count]);   //多项式降阶
        roots[count]*=Complex(R,0);     //得到方程原来的根
        if(originalPoly.fitness(roots[count])<0.9)  //带入最初的多项式检验
        {return false;}
        count++;
        n--;
    }
    if(n==1)
        roots[count]=-R*poly.getRatio(1)/poly.getRatio(0);
    return true;
}

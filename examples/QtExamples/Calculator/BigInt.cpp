#include"BigInt.h"
BigInt::BigInt()
{
	digital[0]=0;   
	len=0;       //当前大整数的长度 
	sign=0;         //符号为正
    isLegal=true;
}

BigInt::BigInt(qllong obj)
{
    if(obj<0)
    {sign=true,obj = -obj;}
    else sign =false;
    digital[0]=obj%BASE;len=0;
    while(obj/=BASE)
    {digital[++len] = obj%BASE;}
    isLegal=true;
}
BigInt::BigInt(const BigInt &obj)
{
	for(len=0,sign=obj.sign;len<=obj.len;len++)
		digital[len]=obj.digital[len];
	len--;
     isLegal=obj.isLegal;
}
BigInt& BigInt::operator =(const BigInt &obj)
{
	for(len=0,sign=obj.sign;len<=obj.len;len++)
		digital[len]=obj.digital[len];
	len--;
     isLegal=obj.isLegal;
	return *this;
}
BigInt& BigInt::operator = (QString qstr)
{
	int i=0,j,k;
    if(qstr[0]=='-')
    {sign=1;}
	else 
    {
        sign=0;
        if(qstr[0]=='+')
            qstr.remove(0,1);
    }
    i=qstr.length();
	for(i=i-BASELEN,k=0;i>=sign;i-=BASELEN,++k)
	{
		for(j=0,digital[k]=0;j<BASELEN;++j)
        {
            if(qstr[i+j]==' ')continue;
            digital[k]=digital[k]*10+qstr[i+j].toLatin1()-'0';
        }
	}
	i+=BASELEN;

	for(j=sign,digital[k]=0;j<i;++j)
    {
        if(qstr[j]==' ')continue;
        digital[k]=digital[k]*10+qstr[j].toLatin1()-'0';
    }
	if(i==sign)k--;
	len=k;
    isLegal=true;
	return *this;
}
BigInt BigInt::operator +(const BigInt &obj)
{
	BigInt sum;
	if(obj.sign==sign)
	{ //同号加;
		int carry=0,i;
		for(i=0;i<=len && i <= obj.len;i++)
		{
			carry = carry +digital[i]+obj.digital[i];
			sum.digital[i] = carry%BASE;
			carry= carry/BASE;
		}
		for(;i<=len;i++)
		{carry = carry + digital[i], sum.digital[i] = carry%BASE, carry/=BASE;}
		for(;i<=obj.len;i++)
		{carry = carry +obj.digital[i], sum.digital[i] = carry%BASE,carry =carry/BASE;}
		if(carry&&i<MAXN){sum.digital[i]=carry;sum.len=i;}
        else if(carry&&i==MAXN){isLegal=false;return *this;}
		else sum.len=i-1;
		sum.sign = sign;
		return sum;
	}
	else 
	{ //异号变同号减法;
		sum = obj;sum.sign= !sum.sign;
		return *this-sum;
	}
}
BigInt BigInt::operator +(int n)
{
	if(n==0)
		return *this;
	if((sign==1&&n<0)||(sign==0&&n>0))
	{
		int temp,carry=0,i=0;
		if(n<0)n=-n;
		BigInt sum;
		if(len==0&&n>=BASE){digital[1]=0;}  
		do
		{
			temp=n%BASE;n/=BASE;
			carry+=digital[i]+temp;
			sum.digital[i]=carry%BASE;
			carry= carry/BASE;
			i++;
		}while(n);
		while(i<=len)
		{
			carry+=digital[i];
			sum.digital[i]=carry%BASE;
			carry=carry/BASE;
			i++;
		}
		if(carry&&i<MAXN){digital[i]=carry,sum.len=i;}
        else if(carry&&i==MAXN){isLegal=false;return *this;}
		else sum.len=i-1;
		sum.sign=sign;
		return sum;
	}
	else
	{
		n=-n;
		return *this-n;
	}
}
BigInt BigInt::operator -(const BigInt &obj)
{
	const BigInt *sub1,*sub2;
	BigInt quotient;
	if(sign==obj.sign)
	{ //同号减;
		int i, carry=0;
		i = this->Cmp(obj,1);                //绝对值比较;
		if(i==0)
			return quotient;                 //返回一个零
		else if(i<0)
			sub1=&obj,sub2=this,quotient.sign=!sign;
		else 
			sub1=this,sub2 = &obj,quotient.sign=sign;
		for(i=0;i<=sub2->len;i++)
		{
			if((quotient.digital[i]=sub1 ->digital[i]-carry-sub2->digital[i])<0)
				carry = 1, quotient.digital[i]+=BASE;      //借位;
			else 
				carry = 0;
		}
		for(;i<=sub1->len;i++)
		{
			if((quotient.digital[i] = sub1->digital[i]-carry )< 0 )
				carry = 1,quotient.digital[i] +=BASE;       //借位;
			else 
				carry = 0;
		}
		do
		{
			--i;
		}while(i&&quotient.digital[i]==0);
		quotient.len = i;
		return quotient;
	}
	else 
	{ //异号变同号加:
		quotient = obj, quotient.sign =!obj.sign;
		return *this + quotient;
	}
}
BigInt BigInt::operator -(int n)
{
	if(n==0)
		return *this;
	if((sign==1&&n<0)||(sign==0&&n>0))
	{
		BigInt quotient;
        qllong carry;
		int i;
		if(n<0)n=-n;
		quotient.sign=sign;
		if(len>1)
		{
			if((quotient.digital[0]=digital[0]-n%BASE)<0)
				carry=1,quotient.digital[0]+=BASE;      //借位;
			else carry=0;
			i=1;
			if(n/=BASE)
			{
				if((quotient.digital[1]=digital[1]-n-carry)<0)
					carry=1,quotient.digital[1]+=BASE;
				else carry=0;
				i=2;
			}
			while(i<=len)
		    {
				if((quotient.digital[i]=digital[i]-carry)<0)
					carry=1,quotient.digital[i]+=BASE;
				else
					carry=0;
				i++;
		    }
			if(quotient.digital[len]==0)
				quotient.len=len-1;
			else quotient.len=len;
		}
		else
		{
			carry=this->FirSecDigit()-n;
			if(carry<0){quotient.sign=true;carry=-carry;}
			quotient.digital[0]=carry%BASE;
			if(carry/=BASE)
			{quotient.digital[1]=carry;quotient.len=1;}
		}
		return quotient;
	}
	else
	{
		n=-n;
		return *this+n;
	}
}
BigInt BigInt::operator *(const BigInt &obj)
{
	int i,j,maxlen;
    qllong carry;
    BigInt product;
	if(this->Zero()||obj.Zero())
		return product;
	maxlen=obj.len+len+1;
    if(maxlen>MAXN){isLegal=false;return *this;}
    memset(product.digital,0,sizeof(qllong)*maxlen );
	for(i = 0; i <= obj.len; i++)
	{
		for(j =0,carry=0;j<=len;j++)
		{
			carry += obj.digital[i] * digital[j] +product.digital[j+i];
			product.digital[j+i] = carry%BASE;
			carry/=BASE;
		}
		if(carry&&i+j<MAXN) 
			product.digital[i+j] = carry;
	}
    if(carry&&maxlen==MAXN)
        {isLegal=false;return *this;}
	if(!carry)maxlen--;
	product.len=maxlen;
	product.sign = sign^obj.sign;
	return product;
}
BigInt BigInt::operator *(int n)
{
	int i,j,maxlen,temp;
    qllong carry;
    BigInt product;
	if(this->Zero()||n==0)return product;

	if(n>=BASE)maxlen=len+2;
	else maxlen=len+1;
	if(n<0){product.sign=!sign,n=-n;}
	else product.sign=sign;
    if(maxlen>MAXN){isLegal=false;return *this;}
    memset(product.digital,0,sizeof(qllong)*maxlen );
	temp=n%BASE;
	for(i=0,carry=0;i<=len;i++)
	{
		carry +=temp*digital[i];
		product.digital[i]=carry%BASE;
		carry/=BASE;
	}
	if(carry&&i<MAXN) product.digital[i] = carry;
    else if(carry&&i==MAXN){isLegal=false;return *this;}
	else product.digital[i]=0;
	if(n/=BASE)
	{
		for(j=1,carry=0;j<=i;++j)
		{
			carry+=product.digital[j]+n*digital[j-1];
			product.digital[j]=carry%BASE;
		    carry/=BASE;
		}
		if(carry&&j<MAXN) product.digital[j]=carry;
        else if(carry&&j==MAXN){isLegal=false;return *this;}
		else maxlen--;
	}
	if(n==0&&!carry)maxlen--;
	product.len=maxlen;
	return product;
}
BigInt BigInt::operator /(const BigInt &obj)
{
	int k;
    qllong div;
	BigInt x,z,res;
	if(this->Zero())return *this;
    if(obj.sign==true||obj.Zero())
        {isLegal=false;return *this;}
	x = *this;
	x.sign=false;
	res.sign=obj.sign^sign;
	while( x.Cmp(obj,1) >0 )
	{
		k = x.len-obj.len;
		if( x.digital[x.len] > obj.digital[obj.len] ) 
			div =x.digital[x.len]/(obj.digital[obj.len]+1);
		else if(x.len>obj.len)
		{
			k--,
			div=(x.digital[x.len]*BASE+x.digital[x.len-1])/(obj.digital[obj.len]+1);
		}
		else break;                  //当x<=obj时跳出循环
		res+=(z=div).Shift(k);
		z*=obj;
		x-=z.Shift(k);
	}
	if(x.Cmp(obj,1)>=0)res=res+1;
	if(res.Zero())res.sign=false;
	else res.sign=sign;
	return res;
}
bool BigInt::operator >(const BigInt &obj)
{
    int i;
    if(len>obj.len)
        return 1;
    if(len<obj.len)
        return 0;
    for(i=len;i>=0;--i)
    {
        if(digital[i]>obj.digital[i])
            return 1;
        if(digital[i]<obj.digital[i])
            return 0;
    }
    return 0;
}
bool BigInt::operator <(const BigInt &obj)
{
    int i;
    if(len<obj.len)
        return 1;
    if(len>obj.len)
        return 0;
    for(i=len;i>=0;--i)
    {
        if(digital[i]<obj.digital[i])
            return 1;
        if(digital[i]>obj.digital[i])
            return 0;
    }
    return 0;
}
BigInt& BigInt::operator +=(const BigInt &obj)
{
	if(obj.sign==sign)
	{ //同号加;
		int carry=0,i;
		for(i=0;i<=len && i <= obj.len;i++)
		{
			carry = carry +digital[i]+obj.digital[i];
			digital[i] = carry%BASE;
			carry= carry/BASE;
		}
		for(;i<=len;i++)
		{carry = carry + digital[i],digital[i] = carry%BASE, carry/=BASE;}
		for(;i<=obj.len;i++)
		{carry = carry +obj.digital[i],digital[i] = carry%BASE,carry =carry/BASE;}
		if(carry&&i<MAXN)digital[i]=carry;
        else if(carry&&i==MAXN){isLegal=false;return *this;}
		len=i-!carry;
		sign = sign;
	}
	else 
	{ //异号变同号减法;
		sign=!sign;
		BigInt temp=obj;
		*this=temp-*this;
	}
	return *this;
}
BigInt& BigInt::operator -=(const BigInt &obj)
{
	const BigInt *sub1,*sub2;
	if(sign==obj.sign)
	{ //同号减;
		int i, carry=0;
		i = this->Cmp(obj,1);                //绝对值比较;
		if(i==0)
		{sign=false;digital[0]=0;len=0;return *this;}//返回一个零
		else if(i<0)
			sub1=&obj,sub2=this,sign=!sign;
		else 
			sub1=this,sub2 = &obj;
		for(i=0;i<=sub2->len;i++)
		{
			if((digital[i]=sub1 ->digital[i]-carry-sub2->digital[i])<0)
				carry=1,digital[i]+=BASE;      //借位;
			else 
				carry = 0;
		}
		for(;i<=sub1->len;i++)
		{
			if((digital[i] = sub1->digital[i]-carry )< 0 )
				carry = 1,digital[i] +=BASE;       //借位;
			else 
				carry = 0;
		}
		do
		{
			--i;
		}while(i&&digital[i]==0);
		len = i;
	}
	else 
	{ //异号变同号加:
		BigInt temp=obj;
		temp.sign =!obj.sign;
		*this=*this+temp;
	}
	return *this;
}
BigInt& BigInt::operator *=(const BigInt &obj)
{
	int i,j,maxlen;
    qllong carry;
    BigInt product;
    if(this->Zero())
    {return *this;}
    if(obj.Zero())
    {*this=obj;return *this;}
	maxlen=obj.len+len+1;
    if(maxlen>MAXN){isLegal=false;return *this;}
    memset(product.digital,0,sizeof(qllong)*maxlen );
	for(i = 0; i <= obj.len; i++)
	{
		for(j =0,carry=0;j<=len;j++)
		{
			carry += obj.digital[i] * digital[j] +product.digital[j+i];
			product.digital[j+i] = carry%BASE;
			carry/=BASE;
		}
		if(carry&&i+j<MAXN) 
			product.digital[i+j] = carry;
	}
    if(carry&&maxlen==MAXN)
        {isLegal=false;return *this;}
	if(!carry)maxlen--;
	product.len=maxlen;
	product.sign = sign^obj.sign;
	*this=product;
	return *this;
}
BigInt BigInt::operator ^(int n)
{
	BigInt temp=*this,res;
	if(n&1){res=temp;}
	else{res.digital[0]=1;}
	n>>=1;
	for(;n>0;n>>=1)
	{
		temp*=temp;
		if(n&1)
		{res*=temp;}
        if(temp.isLegal==false||res.isLegal==false)
        {this->isLegal=false;return *this;}
		//判断数据溢出，已在*=中完成判断。
	}
	return res;
}
BigInt BigInt::operator %(BigInt obj)
{
	int k;
    qllong div;
	BigInt x;
	if(this->Zero())return *this;
    if(obj.Zero()){isLegal=false;return *this;}
	x = *this;
	obj.sign=x.sign=false;
	while( x.Cmp(obj,1) >0 )
	{
		k = x.len-obj.len;
		if( x.digital[x.len] > obj.digital[obj.len] ) 
			div =x.digital[x.len]/(obj.digital[obj.len]+1);
		else if(x.len>obj.len)
		{
			k--,
			div=(x.digital[x.len]*BASE+x.digital[x.len-1])/(obj.digital[obj.len]+1);
		}
		else break;                  //当x<=obj时跳出循环
		x-=(obj*(int)div).Shift(k);
	}
	if(x.Cmp(obj,1)>=0)x-=obj;
	if(x.Zero())x.sign = false;
	else x.sign=sign;
	return x;
}
BigInt& BigInt::operator >>=(int n)
{
	if(n>1)
      *this>>=(n-1);
	if(digital[0]<=1&&len==0)digital[0] = 0;
	else 
	{
		int k=len,t,carry=0;
		if (digital[k]==1)len--;
		while(k>=0)
		{
			t = digital[k]&1;
			digital[k]= digital[k]>>1;
			if(carry)digital[k]+=BASE/2;
			k--;
			carry = t;
		}
	}
	if(this->Zero())sign=0;
	return *this;
}
BigInt& BigInt::operator <<=(int n)
{
	if(Zero())return *this;
	if(n>1)
      *this<<=(n-1);
	int k=0,t,carry=0;
	while(k<=len)
	{
		t=digital[k]<<1;          //t最大值为(BASE-1)*2,不会溢出
		digital[k]=t%BASE;
		if(carry)digital[k]++;
		carry=t/BASE;
		k++;
	}
	if(carry)
	{
		digital[k]=1;len++;
        if(len>MAXN)
            {isLegal=false;return *this;}
	}
	return *this;
}
bool BigInt::Zero()const
{ return digital[0]+len==0;}
qllong BigInt::FirSecDigit()
{
    qllong temp=digital[len];
	if(len>0)
		return temp*BASE+digital[len-1];
	else
		return temp;
}
BigInt BigInt::Sqrt()
{
	//本算法时间复杂度接近线性
    if(sign)   //负数没有平方根
       {isLegal=false;return *this;}
	BigInt res,rem;            //res保留的最终结果，rem保留余数
    qllong temp1,temp2;
	int temp,i;
	double r;
	bool flag;
	res.digital[0]=sqrt((double)digital[len]);
	rem.digital[0]=digital[len]-res.digital[0]*res.digital[0];
	for(i=len-1;i>=0;--i)
	{
		rem=rem.Shift(1),rem.digital[0]=digital[i];     
		/*temp=(int)(rem/(res*20000)); */
		//此处的乘法不复杂，因为商为一个四位数,但是空间消耗很大，因此换用下面的方法
		
		flag=false;
		temp1=rem.FirSecDigit();                          //获取大整数的前两位（16位）
		res=res*20000,temp2=res.FirSecDigit();
		if(temp1<temp2&&rem>res)                          //若temp1<temp2,则temp2除BASE
		{temp2/=BASE;flag=true;}
		temp=temp1/temp2;
		//下面两个条件语句用来精确temp，根据flag选择两种方式来逼近精确值
		if(flag)
		{while((res+temp)*temp>rem)                        //若单纯用temp--，对于有些情况下，效率会很差
			{temp--;}
		}
		else
		{for(r=0.6;(res+temp)*temp>rem;r+=0.1)             //此处非常巧妙，逐渐增大权值，循环次数在5次之内
			{temp=temp1/(temp2+temp*r);}                   //并且当r==1时一定可以得到精确值
         while((res+(temp+1))*(temp+1)<rem)
             temp++;
        }

		rem-=((res+temp)*temp);                           //最终所得余数
		res=(res>>=1)+temp;                               //平方根的值,注意一定要加()
	}
	return res;
}
void BigInt::Factorial(int n)
{
    this->sign=false;
    if(n<0){this->sign=true;n=-n;}
	int i,j,m=0;
    qllong carry;
    digital[0]=1;
    for(i=2;i<=n;i++)
	{
		for(j=0,carry=0;j<=m;j++)
		{  
            carry+=digital[j]*i;
            digital[j]=carry%BASE;
			carry/=BASE;
		}
		if(carry)
		{
            if(m+1>=MAXN)
            {
                isLegal=false;
                return ;
            }
            digital[++m]=carry;
		}
	}
    len=m;
}
void BigInt::Factorial(int n, char c)
{
    this->sign=false;
    if(n<0){this->sign=true;n=-n;}
    int i,j,m=0,work;
    qllong carry;
    if(n&1){work=digital[0]=1;}
    else {work=digital[0]=2;}
    for(i=work+2;i<=n;i+=2)
    {
        for(j=0,carry=0;j<=m;j++)
        {
            carry+=digital[j]*i;
            digital[j]=carry%BASE;
            carry/=BASE;
        }
        if(carry)
        {
            if(m+1>=MAXN)
            {
                isLegal=false;
                return ;
            }
            digital[++m]=carry;
        }
    }
    len=m;
}
BigInt BigInt::Shift(int k)
{
	if(k==0||this->Zero())return *this;
    if(len+k>=MAXN){isLegal=false;return *this;}
	BigInt temp;
	int i;
	temp=*this;
	for(i=0;i<=len;i++)
		temp.digital[i+k]=digital[i];
	for(i=0;i<k;i++)
		temp.digital[i] = 0;
	temp.sign=sign;
	temp.len=len+k;
	return temp;
}
int BigInt::Cmp(const BigInt &obj,bool Is_Abs)
{
	//sign:1表示负数，0表示非负数
	if(!Is_Abs&&(obj.sign^sign))
		return (obj.sign-sign);     //比较正负号
    int k=len-obj.len;        //比较长度;
    if(k!=0)
	{
		if((k>0&&!sign)||(k<0&&sign))
			return 1;
		else
			return -1;
	}
	else
	{
		k=len;
		while(digital[k]==obj.digital[k]&&k>0)
		{--k;}
		if(digital[k]==obj.digital[k])
			return 0;
		if(Is_Abs)
			return digital[k]>obj.digital[k]?1:-1;
		else
		{
			if(digital[k]>obj.digital[k])
				return sign?-1:1;
			else
				return sign?1:-1;
		}
	}
}

void Swap(BigInt *num1,BigInt *num2)
{
    BigInt temp;
    temp=*num1;
    *num1=*num2;
    *num2=temp;
}
QString BigInt::toQString()
{
    QString qstr;
    if(sign==true)
        qstr.append('-');
    qstr.append(QString("%1").arg(digital[len]));
    for(int i=len-1;i>=0;i--)
    {
        qstr.append(QString("%1").arg(digital[i],8,10,QChar('0')));
    }
    return qstr;
}

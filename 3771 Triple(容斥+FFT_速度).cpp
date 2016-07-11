#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int base=1<<17;

const double pi=acos(-1);

struct comp{
	double real,imag;
	comp(double _real=0,double _imag=0):real(_real),imag(_imag){
	}
	operator double() const{
		return real;
	}
	comp operator -() const{
		return comp(-real,-imag);
	}
	comp operator + (const comp &b) const{
		return comp(real+b.real,imag+b.imag);
	}
	comp operator - (const comp &b) const{
		return comp(real-b.real,imag-b.imag);
	}
	comp operator * (const comp &b) const{
		return comp(real*b.real-imag*b.imag,real*b.imag+imag*b.real);
	}
	comp operator * (const double b) const{
		return comp(real*b,imag*b);
	}
	comp operator / (const double b) const{
		return comp(real/b,imag/b);
	}
	comp& operator += (const comp &b){
		real+=b.real;
		imag+=b.imag;
		return *this;
	}
	comp& operator -= (const comp &b){
		real-=b.real;
		imag-=b.imag;
		return *this;
	}
	comp& operator *= (const comp &b){
		return *this=*this*b;
	}
	comp& operator /= (const double b){
		real/=b;
		imag/=b;
		return *this;
	}
	void read(){
		scanf("%lf%lf",&real,&imag);
	}
	void print(){
		printf("%lf+%lfi",real,imag);
	}
};

int n,rev[base];
comp x[4][base];

void init(){
	for(int i=0;i<base;i++){
		rev[i]=0;
		for(int j=1;j<base;j<<=1) (rev[i]<<=1)|=bool(i&j);
	}
}

void FFT(comp *a,int f){
	for(int i=0;i<base;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=1;i<base;i<<=1){
		comp w1(cos(pi/i),(f?-1:1)*sin(pi/i));
		for(int j=0;j<base;j+=i<<1){
			comp w=1;
			for(int k=0;k<i;k++,w*=w1){
				comp x=a[j+k],y=a[j+i+k]*w;
				a[j+k]=x+y;
				a[j+i+k]=x-y;
			}
		}
	}
	if(f) for(int i=0;i<base;i++) a[i]/=base;
}

int main(){
	init();
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int w; scanf("%d",&w);
		x[1][w]+=1;
		x[2][w*2]+=1;
		x[3][w*3]+=1;
	}
	FFT(x[1],0);
	FFT(x[2],0);
	FFT(x[3],0);
	for(int i=0;i<base;i++)
		x[0][i]=
			(x[1][i]*x[1][i]*x[1][i]-x[1][i]*x[2][i]*3.+x[3][i]*2.)/6.
			+(x[1][i]*x[1][i]-x[2][i])/2.
			+x[1][i];
	FFT(x[0],1);
	for(int i=0;i<base;i++){
		double ans=x[0][i];
		if(ans>.1)
			printf("%d %.0lf\n",i,ans);
	}
}

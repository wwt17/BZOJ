#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=1<<18;

const double pi=acos(0)*2;

int n,nn,rev[N];
struct complex{
	double re,im;
	complex(double _re=0,double _im=0):re(_re),im(_im){
	}
	friend complex operator + (const complex &a,const complex &b){
		return complex(a.re+b.re,a.im+b.im);
	}
	friend complex operator - (const complex &a,const complex &b){
		return complex(a.re-b.re,a.im-b.im);
	}
	friend complex operator * (const complex &a,const complex &b){
		return complex(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re);
	}
} q[N],w[2][N],a[N],b[N],f[2][N];

void multiinit(){
	for(int i=0;i<n;i++)
		for(int k=1;k<n;k<<=1) rev[i]=rev[i]<<1|(bool)(i&k);
	for(int i=0;i<n;i++){
		w[0][i]=complex(cos(i*2*pi/n),sin(i*2*pi/n));
		w[1][i]=complex(w[0][i].re,-w[0][i].im);
	}
}

void FFT(complex *a,int f){
	for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
		for(int j=0,t=n/(i<<1);j<n;j+=i<<1)
			for(int k=0,l=0;k<i;k++,l+=t){
				complex
					x=w[f][l]*a[j+i+k],
					y=a[j+k];
				a[j+k]=y+x;
				a[j+i+k]=y-x;
			}
	if(f)
		for(int i=0;i<n;i++) a[i].re/=n;
}

void multi(complex *a,complex *b,complex *c){
	FFT(a,0);
	FFT(b,0);
	for(int i=0;i<n;i++) c[i]=a[i]*b[i];
	FFT(c,1);
}

int main(){
	scanf("%d",&nn);
	for(int i=0;i<nn;i++) scanf("%lf",&q[i].re);
	for(n=1;n<nn;n<<=1); n<<=1;
	multiinit();
	for(int i=0;i<nn;i++) a[i]=q[i];
	b[0]=0; for(int i=1;i<nn;i++) b[i]=1./((long long)i*i);
	multi(a,b,f[0]);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=0;i<nn;i++) a[i]=q[nn-1-i];
	b[0]=0; for(int i=1;i<nn;i++) b[i]=1./((long long)i*i);
	multi(a,b,f[1]);
	for(int i=0;i<nn;i++) printf("%lf\n",f[0][i].re-f[1][nn-1-i].re);
}

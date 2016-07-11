#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi=acos(-1);
typedef long long ll;

struct comp{
	double real,imag;
	comp(double _real=0,double _imag=0):real(_real),imag(_imag){
	}
	friend comp operator + (const comp &a,const comp &b){
		return comp(a.real+b.real,a.imag+b.imag);
	}
	friend comp operator - (const comp &a,const comp &b){
		return comp(a.real-b.real,a.imag-b.imag);
	}
	friend comp operator * (const comp &a,const comp &b){
		return comp(a.real*b.real-a.imag*b.imag,a.real*b.imag+a.imag*b.real);
	}
	void operator /= (const double &k){
		real/=k; imag/=k;
	}
};

const int M=100005,N=1<<18;
int m,n;

int s[M],cnt[N],rev[N];
comp a[N];

void FFT(comp *a,int f){
	for(int i=0;i<n;i++) if(i<rev[i])
		swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1){
		comp w1(cos(pi/i),sin(f*pi/i));
		for(int j=0;j<n;j+=i<<1){
			comp w(1,0);
			for(int k=0;k<i;k++){
				comp x=w*a[j+i+k],y=a[j+k];
				a[j+k]=y+x;
				a[j+i+k]=y-x;
				w=w*w1;
			}
		}
	}
	if(f==-1)
		for(int i=0;i<n;i++) a[i]/=n;
}

void init(){
	for(int i=0;i<n;i++){
		int y=0;
		for(int k=1;k<n;k<<=1) (y<<=1)|=(bool)(i&k);
		rev[i]=y;
	}
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&m);
		// 01:+4  02:+2  1:+6  2:+3  3:+1
		ll ans=0;
		int maxs=0;
		for(int i=0;i<m;i++){
			scanf("%d",&s[i]);
			cnt[s[i]]++;
			maxs=max(maxs,s[i]);
		}
		sort(s,s+m);
		maxs*=2;
		for(n=1;n<=maxs;n<<=1);
		init();
		for(int i=0;i<n;i++) a[i]=cnt[i];
		FFT(a,1);
		for(int i=0;i<n;i++) a[i]=a[i]*a[i];
		FFT(a,-1);
		ll sum=0;
		for(int i=n-1;i>=0;i--){
			ans+=cnt[i]*sum;
			sum+=(ll)round(a[i].real);
		}
		for(int i=0;i<m;i++)
			ans+=(upper_bound(s,s+m,s[i]*2-1)-s)*-3;
		ans+=m*2;
		sum=0;
		for(int i=0;i<n;i++){
			sum+=(ll)round(a[i].real);
			ans+=cnt[i]*sum*-2;
		}
		printf("%.7lf\n",(double)ans/((ll)m*(m-1)*(m-2)));
		for(int i=0;i<m;i++) cnt[s[i]]--;
	}
}

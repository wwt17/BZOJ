#include <cstdio>
#include <algorithm>
#include <vector>
namespace Huge_Num{
	#define SIZEN 20101
	#define INF 0x7FFFFFFF
	using namespace std;
	typedef vector< pair<unsigned,short> > huge_mul;
	huge_mul operator * (huge_mul&,huge_mul&);
	huge_mul operator / (huge_mul&,huge_mul&);
	huge_mul& huge_mul_type(const unsigned n){
		static huge_mul c[SIZEN];
		static unsigned p[SIZEN],prime[SIZEN],primes=0,i=2,j;
		for(;i<=n;++i){
			if(!p[i]) prime[primes++]=p[i]=i,c[i].push_back(make_pair(i,1));
			else c[i]=c[i/p[i]]*c[p[i]];
			for(j=0;j<primes&&prime[j]<=p[i]&&prime[j]*i<SIZEN;++j)
				p[prime[j]*i]=prime[j];
		}
		return c[n];
	}
	unsigned unsigned_int(huge_mul a){
		unsigned ans=1; short j;
		for(huge_mul::iterator i=a.begin();i!=a.end();++i)
			for(j=i->second;j;--j) ans*=i->first;
		return ans;
	}
	void print(huge_mul a){
		if(a.empty()) { putchar('1'); return; }
		for(huge_mul::iterator i=a.begin();i!=a.end();++i){
			if(i!=a.begin()) printf(" * ");
			printf("%u",i->first);
			if(i->second!=1) printf("^%d",i->second);
		}
	}
	void println(huge_mul a){
		print(a); putchar('\n');
	}
	huge_mul operator * (huge_mul &a,huge_mul &b){
		huge_mul ans; short tmp;
		huge_mul::iterator i=a.begin(),j=b.begin();
		while(i!=a.end()&&j!=b.end())
			if(i->first < j->first)
				ans.push_back(*i++); else
			if(i->first > j->first)
				ans.push_back(*j++); else{
			if(tmp=i->second+j->second)
				ans.push_back(make_pair(i->first,tmp));
			i++,j++;
			}
		while(i!=a.end()) ans.push_back(*i++);
		while(j!=b.end()) ans.push_back(*j++);
		return ans;
	}
	huge_mul& operator ~ (huge_mul a){
		for(huge_mul::iterator i=a.begin();i!=a.end();++i) i->second=-i->second;
		return a;
	}
	huge_mul operator / (huge_mul &a,huge_mul &b){
		return a*~b;
	}
	huge_mul& power(huge_mul a,const int k){
		for(huge_mul::iterator i=a.begin();i!=a.end();++i) i->second*=k;
		return a;
	}
	huge_mul factorial(const unsigned n){
		huge_mul f;
		for(unsigned i=2;i<=n;++i)
			f=f*huge_mul_type(i);
		return f;
	}
}
using namespace Huge_Num;
const int N=1005,T=1005;
int t,n,d,tot,a[T];
huge_mul ans;
int x[12000],y[12000];
void mul(int a[],long long b){
	long long x=0;
	for(int i=1;i<=*a;i++){
		x+=a[i]*b;
		a[i]=x%10;
		x/=10;
	}
	while(x){
		a[++*a]=x%10;
		x/=10;
	}
}
void print(int a[]){
	for(int i=*a;i>0;i--) printf("%d",a[i]);
}
void printans(){
	x[0]=x[1]=1;
	y[0]=y[1]=1;
	for(huge_mul::iterator i=ans.begin();i!=ans.end();i++){
		for(int j=0;j<i->second;j++) mul(x,i->first);
		for(int j=0;j>i->second;j--) mul(y,i->first);
	}
	print(x);
	putchar('/');
	print(y);
	putchar('\n');
}
int main(){
	scanf("%d%d%d",&t,&n,&d);
	for(int i=1;i<=t;i++) scanf("%d",&a[i]),tot+=a[i];
	for(int i=1;i<=n;i++){
		int c; scanf("%*d%d",&c);
		if(!a[c]) return puts("0/1"),0;
		ans=ans*huge_mul_type(a[c]);
		ans=ans/huge_mul_type(tot);
		a[c]+=d;
		tot+=d;
	}
	printans();
}

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define ran() ((long long)rand()*RAND_MAX+rand())
inline long long gcd(long long a,long long b){
	long long c;
	while(b){
		c=a%b;
		a=b;
		b=c;
	}
	return a;
}
inline long long lmul(long long a,long long b,const long long p){
	long long c=0;
	for(;b;b>>=1,a<<=1,a%=p) if(b&1) c+=a,c%=p;
	return c;
}
bool is_Prime(long long p){ // Miller-Rabin
	const int sum=10,a[sum]={2,3,5,7,11,13,17,19,23,29};
	if(p==2) return true;
	if(p==1||!(p&1)) return false;
	long long D=p-1;
	while(!(D&1)) D>>=1;
	for(int i=0;i<sum&&a[i]<p;i++){
		long long d=D,t=1,s=a[i];
		for(long long k=d;k;k>>=1,s=lmul(s,s,p)) if(k&1) t=lmul(t,s,p);
		if(t==1) continue;
		while(d<p-1&&t!=p-1){
			t=lmul(t,t,p);
			d<<=1;
		}
		if(d==p-1) return false;
	}
	return true;
}
long long a[100],*newa,o[100],*newo;
void decomp(long long n){ // Pollard-Rho
	if(is_Prime(n)||n==1){ *newa++=n; return; }
	while(true){
		long long c=ran()%n,i=1,x=ran()%n,y=x,k=2;
		do{
			i++;
			long long d=gcd(n+y-x,n);
			if(d>1 && d<n){
				decomp(d);
				decomp(n/d);
				return;
			}
			if(i==k) y=x,k<<=1;
			x=(lmul(x,x,n)+c)%n;
		} while(y!=x);
	}
}
int main(){
	long long m,n;
	while(scanf("%lld%lld",&m,&n)!=EOF){
		if(n%m){ puts("Wario_wins!\n"); continue; }
		newa=a;
		decomp(n/m);
		sort(a,newa);
		newo=o;
		for(long long *i=a;i<newa;){
			int cnt=1;
			for(i++;i<newa&&*(i-1)==*i;i++)
				cnt++;
			*newo++=cnt;
		}
		sort(o,newo);
		puts(newo-o>=1&&o[0]>=8
		  || newo-o>=2&&(o[0]>=5||o[0]>=2&&o[1]>=2)
		  || newo-o>=3&&o[0]>=2
		  || newo-o>=4
			?"Mario_wins!\n"
			:"Wario_wins!\n"
		);
	}
}

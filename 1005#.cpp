//M=没有度数限制的个数 
//T=Sigma{degree[i]-1}
//Ans=M^(n-2-T)*C(n-2,T)*T!/Pi{(degree[i]-1)!}
#include <cstdio>
#include <algorithm>
#include <vector>
namespace Huge_Num{
	#define BASE 10000
	/*
	*/
	huge operator * (const huge &a,const huge &b){
		unsigned i,j; int k;
		huge ans(a.size+b.size);
		for(i=0;i<a.size;++i){
			for(j=0;j<b.size;++j){
				k+=ans[i+j]+a[i]*b[j];
				ans[i+j]=k%BASE;
				k=k/BASE;
			}
			for(;k;++j){
				k+=ans[i+j];
				ans[i+j]%BASE;
				k/=BASE;
			}
		}
		while(ans.size&&!ans[ans.size-1]) --ans.size;
		return ans;
	}
	huge_mul power(huge_mul a,const int k){
		for(unsigned i=0;i<a.size;++i) a.a[i].second+=k;
		return a;
	}
	huge_mul factorial(const unsigned n){
		huge_mul f;
		for(int i=2;i<=n;++i)
			f=f*i;
		return f;
	}
}
using namespace Huge_Num;
int N,i,D[1001],M,T;
huge_mul pi;
int main(){
	scanf("%u",&N);
	for(i=1;i<=N;++i){
		scanf("%d",D+i);
		if(D[i]==-1) ++M; else T+=--D[i],pi=pi*D[i];
	}
	if(T>N-2) puts("0");
}

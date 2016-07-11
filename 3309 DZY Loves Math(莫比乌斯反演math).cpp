/*
sigma(i) sigma(j) f(gcd(i,j))  i<=a, j<=b
sigma(d1) sigma(i) sigma(j) f(d1)*e(gcd(i,j))  i<=a/d1, j<=b/d1
sigma(d1) sigma(d2) sigma(i) sigma(j) f(d1)*miu(d2) i<=a/d1, j<=b/d1, d2|gcd(i,j)
sigma(d1) sigma(d2) (a/d1/d2)*(b/d1/d2) f(d1)*miu(d2)
sigma(D) (a/D)*(b/D)* sigma(d) f(d)*miu(D/d) d|D

f(i)= max(f(i/p[i]),cnt(i))
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1e7+5;
typedef long long ll;
int primes,prime[N],p[N],pp[N],cnt[N],g[N];
void init(){
	for(int i=2;i<N;i++){
		if(!p[i])
			p[i]=prime[primes++]=i;
		if(p[i]==p[i/p[i]]){
			cnt[i]=cnt[i/p[i]]+1;
			pp[i]=pp[i/p[i]];
		}
		else{
			cnt[i]=1;
			pp[i]=i/p[i];
		}
		if(pp[i]==1)
			g[i]=1;
		else
			if(cnt[i]==cnt[pp[i]])
				g[i]=-g[pp[i]];
			else
				g[i]=0;
		for(int j=0;j<primes&&i*prime[j]<N&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
	for(int i=2;i<N;i++) g[i]+=g[i-1];
}
int main(){
	init();
	int t; scanf("%d",&t);
	while(t--){
		int a,b; scanf("%d%d",&a,&b);
		ll ans=0;
		for(int i=0;i<a&&i<b;){
			int j=min(a/(a/(i+1)),b/(b/(i+1)));
			ans+=(ll)(g[j]-g[i])*(a/j)*(b/j);
			i=j;
		}
		printf("%lld\n",ans);
	}
}

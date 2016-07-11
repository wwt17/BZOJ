#include <cstdio>
#include <algorithm>
using namespace std;
const int N=10000005;
int n,m,i,primes,prime[N/2],p[N],miu[N],g[N];
void init(){
	miu[1]=1;
	g[1]=1;
	for(int i=2;i<N;i++){
		if(!p[i]){
			p[i]=prime[primes++]=i;
			miu[i]=-1;
			g[i]=1;
		}
		for(int j=0;j<primes&&i*prime[j]<N&&prime[j]<=p[i];j++){
			p[i*prime[j]]=prime[j];
			if(prime[j]==p[i]){
				miu[i*prime[j]]=0;
				g[i*prime[j]]=miu[i];
			}
			else{
				miu[i*prime[j]]=-miu[i];
				g[i*prime[j]]=miu[i]-g[i];
			}
		}
		g[i]+=g[i-1];
	}
}
long long calc(int n,int m){
	long long ans=0;
	if(n>m) swap(n,m);
	for(int i=2,j;i<=n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		ans+=(long long)(g[j]-g[i-1])*(n/i)*(m/i);
	}
	return ans;
}
int main(){
	init();
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%lld\n",calc(n,m));
	}
}

#include <cstdio>
typedef long long ll;
const int N=int(1e7)+5,P=20101009;

int n,m,primes,prime[N],p[N],g[N];

int main(){
	scanf("%d%d",&n,&m);
	if(n>m){
		int t=n; n=m; m=t;
	}
	g[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]){
			p[i]=prime[primes++]=i;
		}
		if(p[i]!=p[i/p[i]])
			g[i]=ll(g[i/p[i]])*(1-p[i])%P;
		else
			g[i]=g[i/p[i]];
		for(int j=0;j<primes&&prime[j]<=p[i]&&i*prime[j]<=n;j++)
			p[i*prime[j]]=prime[j];
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ll x=n/i,y=m/i;
		ans=(ans+(((x+1)*x>>1)%P)*(((y+1)*y>>1)%P)%P*i%P*g[i])%P;
	}
	printf("%d\n",int((ans+P)%P));
}

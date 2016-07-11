#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=(int)1e7,mo=(int)1e9+7;

ll power(ll a,ll b){
	a%=mo;
	if((b%=mo-1)<0) b+=mo-1;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

int prime[N/2+5],p[N+5],mu[N+5],smu[N+5];

int s,m,k,L,R;
ll ans;

void init(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		if(p[i/p[i]]==p[i]) mu[i]=0; else mu[i]=-mu[i/p[i]];
		for(int j=1;j<=*prime&&i*prime[j]<=n&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
	for(int i=1;i<=n;i++) smu[i]=smu[i-1]+mu[i];
}

int summu(int n){
	if(n<=s) return smu[n];
	int ans=1;
	for(int l=0,r,last=0,now;n/(l+1)>1;l=r,last=now){
		r=n/(n/(l+1));
		now=summu(r);
		ans=(ans-(now-last)*(n/r-1LL))%mo;
	}
	return ans;
}

int main(){
	scanf("%d%d%d%d",&m,&k,&L,&R); L--; L/=k; R/=k;
	s=min(R,N);
	init(s);
	int ans=0;
	for(int l=0,r,last=0,now;l<R;l=r,last=now){
		r=min(l+1>L?R:L/(L/(l+1)),R/(R/(l+1)));
		now=summu(r);
		ans=(ans+(now-last)*power(R/r-L/r,m))%mo;
	}
	printf("%d\n",(ans+mo)%mo);
}

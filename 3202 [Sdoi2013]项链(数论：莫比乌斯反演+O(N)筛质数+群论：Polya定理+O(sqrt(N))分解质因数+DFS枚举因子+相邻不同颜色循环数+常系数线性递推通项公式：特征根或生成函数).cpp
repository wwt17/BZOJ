#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mo=1000000007,mo2=mo*mo;
const int A=(int)1e7+5;

ll seq[10][2];
int maxa;
int prime[A/2],p0[A],mu[A];
ll inv[10];

ll mul(ll a,ll b){
	ll ans=0;
	for(;b;b>>=1){
		if(b&1) if((ans+=a)>=mo2) ans-=mo2;
		if((a<<=1)>=mo2) a-=mo2;
	}
	return ans;
}
ll power(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
	}
	return ans;
}

void init(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!p0[i]) p0[i]=prime[++*prime]=i,mu[i]=-1;
		for(int j=1;j<=*prime&&i*prime[j]<=n&&prime[j]<=p0[i];j++){
			p0[i*prime[j]]=prime[j];
			mu[i*prime[j]]=prime[j]==p0[i]?0:-mu[i];
		}
		mu[i]+=mu[i-1];
	}
	inv[1]=1;
	for(int i=2;i<10;i++) inv[i]=mul(mo2-mo2/i,inv[mo2%i]);
}

ll C(ll n,int m){
	ll ans=1;
	for(int i=1;i<=m;i++) ans=mul(mul(ans,n-i+1),inv[i]);
	return ans;
}

ll work1(int n){
	ll ans=0;
	for(int l=0,r;l<n;l=r){
		int v=n/(l+1);
		r=n/v;
		(ans+=mul(mu[r]-mu[l],C(v+2,3)))%=mo2;
	}
	return ans;
}

int k;
ll p[100],q[100];

void decomp(ll n){
	k=0;
	for(ll i=2;i*i<=n;i++) if(n%i==0){
		p[k]=i;
		q[k]=0;
		do{
			q[k]++;
			n/=i;
		} while(n%i==0);
		k++;
	}
	if(n>1){
		p[k]=n;
		q[k]=1;
		k++;
	}
}

ll n,c,ans;

ll f(ll n){
	return (power(c,n)+(n&1?mo2-c:c))%mo2;
}

void dfs(int i,ll d,ll phi){
	if(i==k){
		if((ans+=mul(phi,f(n/d)))>=mo2) ans-=mo2;
		return;
	}
	dfs(i+1,d,phi);
	for(int j=1;j<=q[i];j++){
		d*=p[i];
		phi*=p[i]-(j==1);
		dfs(i+1,d,phi);
	}
}

int work2(ll n,int a){
	::n=n;
	ans=0;
	c=(work1(a)+mo2-1)%mo2;
	decomp(n);
	dfs(0,1,1);
	if(n%mo)
		ans=mul(ans,power(n,mo-2))%mo;
	else
		ans=mul(ans,power(n/mo,mo-2))/mo;
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	for(int i=0;i<T;i++){
		scanf("%lld%lld",&seq[i][0],&seq[i][1]);
		maxa=max(maxa,(int)seq[i][1]);
	}
	init(maxa);
	for(int i=0;i<T;i++)
		printf("%d\n",work2(seq[i][0],seq[i][1]));
}

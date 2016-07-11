#include <cstdio>
typedef long long ll;
const int mo=999911659,P[4]={2,3,4679,35617};
int n;
ll power(ll a,ll b,ll mo){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
ll fac[36000],ifac[36000];

ll exgcd(ll a,ll &x,ll b,ll &y,ll c){
	if(!b){
		x=c/a;
		y=0;
		return a;
	}
	ll g=exgcd(b,y,a%b,x,c);
	y-=a/b*x;
	ll d=x/b;
	x-=d*b;
	y+=d*a;
	return g;
}

ll crt(ll p1,ll c1,ll p2,ll c2){
	ll k1,k2;
	exgcd(p1,k1,p2,k2,c2-c1);
	return ((k1%p2+p2)%p2*p1+c1)%(p1*p2);
}

ll lucas(ll n,ll m,ll mo){
	ll ans=1;
	for(;n||m;n/=mo,m/=mo){
		ll a=n%mo,b=m%mo;
		if(b>a) return 0;
		ans=ans*fac[a]%mo*ifac[b]%mo*ifac[a-b]%mo;
	}
	return ans;
}
ll calc(ll mo){
	fac[0]=1;
	for(int i=1;i<mo;i++) fac[i]=fac[i-1]*i%mo;
	ifac[mo-1]=power(fac[mo-1],mo-2,mo);
	for(int i=mo-1;i>=1;i--) ifac[i-1]=ifac[i]*i%mo;
	ll d,ans=0;
	for(d=1;d*d<n;d++) if(n%d==0)
		ans=(ans+lucas(n,d,mo)+lucas(n,n/d,mo))%mo;
	if(d*d==n)
		ans=(ans+lucas(n,d,mo))%mo;
	return ans;
}

int main(){
	int g;
	scanf("%d%d",&n,&g);
	if((g%=mo)==0) return puts("0"),0;
	ll p=1,c=0;
	for(int i=0;i<4;i++){
		c=crt(p,c,P[i],calc(P[i]));
		p*=P[i];
	}
	printf("%d\n",(int)power(g,c,mo));
}

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=10005;
typedef pair<ll,ll> pii;
int Mo,cnt,k,p[10],q[10],mo[10],phi[10],n1,n2;
ll n,m,a[20];

ll power(ll a,ll b,ll mo){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

void exgcd(ll a,ll b,ll c,ll &x,ll &y){
	if(!b){
		x=c/a;
		y=0;
		return;
	}
	exgcd(b,a%b,c,y,x);
	y-=a/b*x;
}

void decomp(int x){
	for(int i=2;i*i<=x;i++) if(x%i==0){
		p[cnt]=i;
		mo[cnt]=1;
		while(x%i==0){
			x/=i;
			q[cnt]++;
			mo[cnt]*=i;
		}
		phi[cnt]=mo[cnt]/p[cnt]*(p[cnt]-1);
		cnt++;
	}
	if(x>1){
		p[cnt]=x;
		q[cnt]=1;
		mo[cnt]=x;
		phi[cnt]=x-1;
		cnt++;
	}
}

int fact[10][N];

void initfac(){
	for(k=0;k<cnt;k++){
		fact[k][0]=1;
		for(int i=1;i<=mo[k];i++)
			fact[k][i]=1LL*fact[k][i-1]*(i%p[k]?i:1)%mo[k];
	}
}

ll count(ll n){
	return n?count(n/p[k])+n/p[k]:0;
}
ll getval(ll n){
	return n?getval(n/p[k])*power(fact[k][mo[k]],n/mo[k],mo[k])%mo[k]*fact[k][n%mo[k]]%mo[k]:1;
}

ll C(ll n,ll m){
	if(n<0||m<0||m>n) return 0;
	ll c=count(n)-count(n-m)-count(m);
	return c>=q[k]?0:getval(n)*power(getval(n-m)*getval(m)%mo[k],phi[k]-1,mo[k])%mo[k]*power(p[k],c,mo[k])%mo[k];
}

pii crt(pii a1,pii a2){
	ll k1,k2;
	exgcd(a1.second,-a2.second,a2.first-a1.first,k1,k2);
	k1=(k1%a2.second+a2.second)%a2.second;
	return pii((k1*a1.second+a1.first)%(a1.second*a2.second),a1.second*a2.second);
}

int calc(){
	ll ans=0;
	for(int s=0;s<1<<n1;s++){
		int c=0;
		for(int i=0;i<n1;i++) if(s>>i&1){
			c++;
			m-=a[i];
		}
		(ans+=(c&1?-1:1)*C(m-1,n-1))%=mo[k];
		for(int i=0;i<n1;i++) if(s>>i&1) m+=a[i];
	}
	return (ans+mo[k])%mo[k];
}

int Main(){
	scanf("%lld%d%d%lld",&n,&n1,&n2,&m);
	for(int i=0;i<n1+n2;i++) scanf("%lld",&a[i]);
	for(int i=n1;i<n1+n2;i++) m-=a[i]-1;
	pii ans(0,1);
	for(k=0;k<cnt;k++)
		ans=crt(ans,pii(calc(),mo[k]));
	return ans.first;
}

int main(){
	int T;
	scanf("%d%d",&T,&Mo);
	decomp(Mo);
	initfac();
	while(T--)
		printf("%d\n",Main());
}

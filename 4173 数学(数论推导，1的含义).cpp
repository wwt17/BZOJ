#include <cstdio>
typedef long long ll;
const int mo=998244353;
ll n,m;

ll phi(ll n){
	ll ans=1;
	for(ll i=2;i*i<=n;i++) if(n%i==0){
		n/=i;
		ans*=i-1;
		while(n%i==0) n/=i,ans*=i;
	}
	if(n!=1) ans*=n-1;
	return ans;
}

int main(){
	scanf("%lld%lld",&n,&m);
	printf("%d\n",int( (phi(n)%mo)*(phi(m)%mo)%mo*(n%mo)%mo*(m%mo)%mo ));
}

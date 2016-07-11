#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mo=19940417;
ll n,m;
ll f(ll m,ll n){ // sum(i<=n) m/i*i
	ll ans=0;
	for(ll l=0,r,vl=0,vr;l<n;l=r,vl=vr){
		r=min(m/(m/(l+1)),n);
		vr=r*(r+1)/2%mo;
		(ans+=m/r*(vr-vl))%=mo;
	}
	return ans;
}
ll calc(ll n){
	ll n2=n+1,n3=2*n+1;
	switch(n%3){
		case 0: n/=3; break;
		case 1: n3/=3; break;
		case 2: n2/=3; break;
	}
	if(n%2==0) n/=2; else n2/=2;
	return n*n2%mo*n3%mo;
}
ll g(ll n,ll m){ // sum(i<=n) (n/i)*(m/i)*i*i
	ll ans=0;
	for(ll l=0,r,vl=0,vr;l<n;l=r,vl=vr){
		r=min(min(n/(n/(l+1)),m/(m/(l+1))),n);
		vr=calc(r);
		(ans+=(n/r)*(m/r)%mo*(vr-vl))%=mo;
	}
	return ans;
}
int main(){
	scanf("%lld%lld",&n,&m);
	if(n>m){ ll t=n; n=m; m=t; }
	ll ans;
	printf("%lld\n",ans=(((n*n%mo-f(n,n))*(m*m%mo-f(m,m))%mo-n*m%mo*n%mo+f(n,n)*m%mo+f(m,n)*n%mo-g(n,m))%mo+mo)%mo);
}

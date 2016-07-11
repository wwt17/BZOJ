#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxN=205;
int N,n;
ll M,F;
struct data{
	ll s,p;
	friend bool operator < (const data &a,const data &b){
		return a.s<b.s||a.s==b.s&&a.p<b.p;
	}
} a[maxN];
ll f[maxN];
ll ceil(ll x,ll y){
	return x/y+bool(x%y);
}
ll floor(ll x,ll y){
	return x/y;
}
ll calc(int i,ll x){
	return a[i-1].s*x+floor(M-(f[i-1]+F)*x,a[i].p);
}
int main(){
	scanf("%lld%lld%d",&M,&F,&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].p,&a[i].s),a[i].s++;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(N&&a[N].p>=a[i].p) N--;
		a[++N]=a[i];
	}
	ll ans=0;
	for(int i=1;i<=N;i++){
		if(f[i-1]+1.*(a[i].s-a[i-1].s)*a[i].p>2e18){
			f[i]=2e18;
		}
		else
			f[i]=f[i-1]+(a[i].s-a[i-1].s)*a[i].p;
	}
	for(int i=1;i<=N;i++){
		ll a=ceil(M,f[i]+F),b=floor(M,f[i-1]+F);
		if(a<=b)
			ans=max(ans,max(calc(i,a),calc(i,b)));
	}
	ll b=floor(M,f[N]+F);
	if(0<=b)
		ans=max(ans,a[N].s*b);
	printf("%lld\n",ans);
}

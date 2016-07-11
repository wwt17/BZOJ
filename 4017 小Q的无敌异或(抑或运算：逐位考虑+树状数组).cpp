#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=(int)1e5+5,mo=998244353;

int n,m,a[N];
ll b[N],c[N],o[N];
int base,t[N];

int query(ll bnd){
	int x=0,cnt=0;
	for(int j=base;j;j>>=1)
		if(x+j<=m&&o[x+j]<=bnd)
			cnt+=t[x+=j];
	return cnt;
}
void add(ll val){
	int x=0;
	for(int j=base;j;j>>=1)
		if(x+j<=m&&o[x+j]<=val)
			x+=j;
	for(;x<=m;x+=x&-x) t[x]++;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>m) m=a[i];
	}
	ll ans=0;
	for(int i=1;i<=n;i++) b[i]=b[i-1]^a[i];
	for(int k=0;m>>k;k++){
		ll now=0;
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(b[i]>>k&1){
				now+=i-cnt;
				cnt++;
			}
			else{
				now+=cnt;
			}
		}
		ans=(ans+((now%mo)<<k))%mo;
	}
	printf("%lld ",ans);
	ans=0;
	for(int i=1;i<=n;i++) b[i]=b[i-1]+a[i];
	for(int k=0;b[n]>>k;k++){
		o[1]=0;
		for(int i=1;i<=n;i++) o[i+1]=c[i]=b[i]&((1LL<<k+1)-1);
		sort(o+1,o+(n+1)+1);
		m=unique(o+1,o+(n+1)+1)-o-1;
		for(base=1;base<=m;base<<=1); base>>=1;
		for(int i=1;i<=m;i++) t[i]=0;
		add(0);
		for(int i=1;i<=n;i++){
			ll r=(c[i]-(1LL<<k))&((1LL<<k+1)-1),l=c[i];
			ans^=((query(r)-query(l)+(l<=r?0:i))&1LL)<<k;
			add(c[i]);
		}
	}
	printf("%lld\n",ans);
}

#include <cstdio>
#include <set>
using namespace std;

typedef long long ll;

const int N=200005;

int n;
ll m,s,a;
set<ll> S;

int main(){
	scanf("%d%lld",&n,&m);
	S.insert(s=0);
	ll ans=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		s=((s+a)%m+m)%m;
		set<ll>::iterator it=++S.insert(s).first;
		if(it==S.end()) it=S.begin();
		ans=max(ans,(s-*it+m)%m);
	}
	printf("%lld\n",ans);
}

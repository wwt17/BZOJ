#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1000,B=63;
int n;
ll base[B];
inline bool add(ll x){
	for(int i=B-1;i>=0;i--) if(x>>i&1)
		if(base[i]) x^=base[i];
		else{ base[i]=x; return true; }
	return false;
}
struct data{
	ll num; int w;
	bool operator < (const data &b) const{
		return w>b.w;
	}
} a[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld%d",&a[i].num,&a[i].w);
	sort(a,a+n);
	int ans=0;
	for(int i=0;i<n;i++)
		if(add(a[i].num))
			ans+=a[i].w;
	printf("%d\n",ans);
	scanf("\n");
}

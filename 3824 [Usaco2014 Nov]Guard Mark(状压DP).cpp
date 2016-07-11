#include <cstdio>
#include <algorithm>
using namespace std;
const int N=20;
typedef long long ll;
const ll inf=1e18;
int n,h;
ll ans=-inf,height[N],weight[N],strength[N],f[1<<N],g[1<<N];
int main(){
	scanf("%d%d",&n,&h);
	for(int i=0;i<n;i++) scanf("%lld%lld%lld",height+i,weight+i,strength+i);
	f[0]=inf;
	g[0]=0;
	for(int s=1;s<1<<n;s++){
		f[s]=-inf;
		for(int i=0;i<n;i++) if(s>>i&1){
			int t=s^(1<<i);
			if(weight[i]<=f[t])
				f[s]=max(f[s],min(f[t]-weight[i],strength[i]));
			g[s]=g[t]+height[i];
		}
		if(g[s]>=h) ans=max(ans,f[s]);
	}
	if(ans>=0) printf("%lld\n",ans); else puts("Mark is too tall");
}

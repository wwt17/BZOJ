#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1000005;
int n,m,k,a[N];
long long x,y,s[N],f[N][2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+n+1);
	for(int i=n;i;i--) s[i]=s[i+1]+a[i];
	x=y=-1e16;
	for(int i=1;i<=n;i++){
		f[i][0]+=x; f[i][1]+=y;
		if(a[i]&1) x=a[i]; else y=a[i];
	}
	x=y=1e16;
	for(int i=n;i;i--){
		if(a[i]&1) x=a[i]; else y=a[i];
		f[i][1]-=x; f[i][0]-=y;
	}
	scanf("%d",&m);
	while(m--){
		int k; scanf("%d",&k);
		long long ans=s[n-k+1]+(s[n-k+1]&1?0:max(f[n-k+1][0],f[n-k+1][1]));
		if(ans<-5e15) puts("-1"); else
		printf("%lld\n",ans);
	}
}

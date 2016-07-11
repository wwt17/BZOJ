#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001,K=16;
int k,n,ans=-1,s[N],v[K],*f[1<<K];
int main(){
	scanf("%d%d",&k,&n);
	for(int j=0;j<k;j++) scanf("%d",&v[j]);
	for(int i=0;i<n;i++) scanf("%d",&s[i+1]),s[i+1]+=s[i];
	f[0]=s;
	for(int i=0;i<1<<k;i++){
		int sum=0;
		for(int j=0;j<k;j++) if(!(i&1<<j)){
			sum+=v[j];
			f[i|1<<j]=max(f[i|1<<j],upper_bound(f[i],s+n+1,*f[i]+v[j])-1);
		}
		if(f[i]==s+n) ans=max(ans,sum);
	}
	printf("%d\n",ans);
}

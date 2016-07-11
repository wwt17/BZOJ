#include <cstdio>
#include <algorithm>
using namespace std;
const int N=10005,K=105;
int n,k,a[N],f[K],cnt[N][K][2];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=k;j;j--)
			cnt[i][j][0]=cnt[i-1][j][0]+cnt[i][j+1][0]-cnt[i-1][j+1][0]+(a[i]==j);
	for(int i=n;i;i--)
		for(int j=1;j<=k;j++)
			cnt[i][j][1]=cnt[i+1][j][1]+cnt[i][j-1][1]-cnt[i+1][j-1][1]+(a[i]==j);
	for(int i=1;i<=n;i++) if(a[i]==-1){
		for(int j=2;j<=k;j++) f[j]=min(f[j-1],f[j]);
		for(int j=1;j<=k;j++) f[j]+=cnt[i][j+1][0]+cnt[i][j-1][1];
	}
	else
		for(int j=1;j<=k;j++) f[j]+=cnt[i][a[i]+1][0];
	int ans=N*N;
	for(int j=1;j<=k;j++) ans=min(ans,f[j]);
	printf("%d\n",ans);
}

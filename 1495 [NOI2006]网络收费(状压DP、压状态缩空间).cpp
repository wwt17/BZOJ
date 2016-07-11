// f[i][j][k]=min{ f[i<<1][jj][k<<1|this]+f[i<<1|1][(1<<n-high[i])-jj][k<<1|this] }
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=10,inf=1.05e9;
int n,high[1<<N],a[1<<N],cost[1<<N][2],sum[1<<N][N+1],f[1<<N+1][1<<N+1];
int main(){
	scanf("%d",&n);
	for(int i=0;i<1<<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<1<<n;i++) scanf("%d",&cost[i][a[i]^1]);
	for(int i=2;i<1<<n;i++) high[i]=high[i>>1]+1;
	for(int i=0;i<1<<n;i++)
		for(int j=i+1;j<1<<n;j++){
			int x; scanf("%d",&x);
			int k=high[i^j]+1;
			sum[i][k]+=x;
			sum[j][k]+=x;
		}
	for(int i=0;i<1<<n;i++)
		for(int s=0;s<1<<n+1;s++){
			f[1<<n|i][s]=cost[i][s&1];
			for(int k=1;k<=n;k++) if((s>>k&1)==(s&1))
				f[1<<n|i][s]+=sum[i][k];
		}
	for(int i=(1<<n)-1;i;i--)
		for(int s=0;s<1<<n+1;s++){
			f[i][s]=inf;
			int k=s>>n-high[i]+1,j=s&(1<<n-high[i]+1)-1;
			if(j>(1<<n-high[i])) continue;
			int kk=(k<<1|( (1<<n-high[i])-j>=j ))<<n-high[i];
			for(int jj=max(0,j-(1<<n-high[i]-1));jj<=min(1<<n-high[i]-1,j);jj++)
				f[i][s]=min(f[i][s],f[i<<1][kk|jj]+f[i<<1|1][kk|j-jj]);
		}
	int ans=inf;
	for(int s=0;s<1<<n+1;s++) ans=min(ans,f[1][s]);
	printf("%d\n",ans);
}

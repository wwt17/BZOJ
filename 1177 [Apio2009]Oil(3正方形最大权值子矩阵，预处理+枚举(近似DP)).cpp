#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1505;
int m,n,k,map[N][N],sum[N][N],s[N][N],ul[N][N],ur[N][N],dl[N][N],dr[N][N];
#define max3(a,b,c) max(max(a,b),c)
int main(){
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&map[i][j]);
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
		}
	}
	for(int i=k;i<=m;i++)
		for(int j=k;j<=n;j++)
			s[i][j]=sum[i][j]-sum[i-k][j]-sum[i][j-k]+sum[i-k][j-k];
	
	for(int i=k;i<=m;i++){
		for(int j=k;j<=n;j++)
			ul[i][j]=max3(ul[i-1][j],ul[i][j-1],s[i][j]);
		for(int j=n-k+1;j>=1;j--)
			ur[i][j]=max3(ur[i-1][j],ur[i][j+1],s[i][j+k-1]);
	}
	for(int i=m-k+1;i>=1;i--){
		for(int j=k;j<=n;j++)
			dl[i][j]=max3(dl[i+1][j],dl[i][j-1],s[i+k-1][j]);
		for(int j=n-k+1;j>=1;j--)
			dr[i][j]=max3(dr[i+1][j],dr[i][j+1],s[i+k-1][j+k-1]);
	}
	
	int ans=0;
	
	for(int i=k;i<=m-k;i++)
		for(int j=k;j<=n-k;j++)
			ans=max(ans,ul[i][j]+ur[i][j+1]+dr[i+1][1]),
			ans=max(ans,dl[i+1][j]+dr[i+1][j+1]+ur[i][1]),
			ans=max(ans,ul[i][j]+dl[i+1][j]+dr[1][j+1]),
			ans=max(ans,ur[i][j+1]+dr[i+1][j+1]+dl[1][j]);
	
	for(int i=k;i<=m-2*k;i++)
		for(int j=k;j<=n;j++)
			ans=max(ans,ur[i][1]+s[i+k][j]+dr[i+k+1][1]);
	for(int j=k;j<=n-2*k;j++)
		for(int i=k;i<=m;i++)
			ans=max(ans,dl[1][j]+s[i][j+k]+dr[1][j+k+1]);
	
	printf("%d\n",ans);
}

#include <cstdio>
const int N=205,mo=9999973;
int n,m,ans,f[N*2][N*2],g[N*2][N*2];
void renew(int &a,long long b){
	a=(a+b)%mo;
}
int main(){
	scanf("%d%d",&n,&m);
	f[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++)
			for(int k=0;j+k<=m;k++) if(f[j][k]){
				int t=m-j-k;
				(g[j][k]+=f[j][k])%=mo;
				if(t) renew(g[j+1][k],1LL*t*f[j][k]);
				if(j) renew(g[j-1][k+1],1LL*j*f[j][k]);
				if(t>=2) renew(g[j+2][k],t*(t-1)/2LL%mo*f[j][k]);
				if(j>=2) renew(g[j-2][k+2],j*(j-1)/2LL%mo*f[j][k]);
				if(t>=1&&j>=1) renew(g[j][k+1],t*j*1LL%mo*f[j][k]);
			}
		for(int j=0;j<=m;j++)
			for(int k=0;j+k<=m;k++)
				f[j][k]=g[j][k],g[j][k]=0;
	}
	for(int j=0;j<=m;j++)
		for(int k=0;j+k<=m;k++)
			renew(ans,f[j][k]);
	printf("%d\n",ans);
	scanf("\n");
}

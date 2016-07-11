#include <cstdio>
const int N=10,M=50;
typedef double real;
int n,m;

int cnt[1<<N];
real fac[M],C[M][M],f[1<<N][M],g[1<<N][M];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=m;i++) fac[i]=i?fac[i-1]*i:1;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=j?C[i-1][j-1]+C[i-1][j]:1;
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d",&x,&y); x--,y--;
		for(int s=0;s<1<<n;s++) if((s>>x&1)&&(s>>y&1)) cnt[s]++;
	}
	for(int s=1;s<1<<n;s++) for(int j=0;j<=cnt[s];j++){
		if(s==(s&-s)){
			f[s][j]=1;
			g[s][j]=1;
			continue;
		}
		if(j==0) continue;
		f[s][j]=0;
		int ss=s-(s&-s);
		for(int t=ss;t;t=(t-1)&ss) for(int k=0;k<j;k++) if(k<=cnt[t]&&j-1-k<=cnt[s^t]){
			f[s][j]+=g[t][k]*g[s^t][j-1-k]*C[j-1][k]*(cnt[s]-cnt[t]-cnt[s^t])*C[cnt[s]-j][cnt[t]-k]*C[cnt[s]-j-(cnt[t]-k)][cnt[s^t]-(j-1-k)]*fac[cnt[s]-cnt[t]-cnt[s^t]-1];
		}
		g[s][j]=g[s][j-1]+f[s][j];
	}
	int s=(1<<n)-1;
	real ans=0;
	for(int j=0;j<=m;j++) ans+=j*f[s][j];
	ans/=(m+1.)*fac[m];
	printf("%.6lf\n",(double)ans);
}

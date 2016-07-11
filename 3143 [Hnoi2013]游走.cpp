#include <cstdio>
#include <algorithm>
#include <functional>
int n,m,i,j,ii; short u[200000],v[200000];
double d[501],f[501][501],ans[501],base,w[200000];
inline void read(short &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
int main(){
	double r;scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i) read(u[i]),read(v[i]),++d[u[i]],++d[v[i]];
	for(i=1;i<=n;++i) d[i]=1/d[i];
	for(i=1;i<=m;++i) f[v[i]][u[i]]=d[u[i]],f[u[i]][v[i]]=d[v[i]];
	ans[n]=0;
	for(i=1;i<=n;++i) f[i][i]=-1,f[i][0]=0,f[i][n]=0; f[1][0]=-1;
	for(i=1;i<=n;++i){
		for(ii=i+1;ii<=n;++ii){
			f[ii][0]-=f[i][0]*(base=f[ii][i]/f[i][i]);
			for(j=i;j<=n;++j) f[ii][j]-=f[i][j]*base;
		}
	}
	for(i=n-1;i;--i){
		ans[i]=f[i][0];
		for(j=n;i<j;--j) ans[i]-=f[i][j]*ans[j];
		ans[i]/=f[i][i];
	}
	for(i=1;i<=m;++i) w[i]=ans[u[i]]+ans[v[i]];
	for(i=1;i<=n;++i) ans[i]*=d[i];
	for(i=1;i<=m;++i) w[i]=ans[u[i]]+ans[v[i]];
	std::sort(w+1,w+m+1,std::greater<double>());
	double Ans=0; for(i=1;i<=m;++i) Ans+=w[i]*i;
	printf("%.3f\n",Ans);
}

#include <cstdio>
#include <vector>
using namespace std;
typedef double db;
const int N=105,M=1005;
const db oo=1./0;
inline void maxi(db &a,const db b){
	if(b>a) a=b;
}
int n,m,v0;
db ans,rho[N],w[N];
vector<int> graph[N];
db f[N][N][N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf",&w[i]);
	scanf("%d%lf",&v0,&rho[1]);
	rho[0]=1;
	for(int i=2;i<=n;i++) rho[i]=rho[i-1]*rho[1];
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d",&x,&y);
		graph[x].push_back(y);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[0][i][j]=i==j?0:-oo;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[k][i][j]=-oo;
		for(int i=1;i<=n;i++)
			for(vector<int>::iterator it=graph[i].begin();it!=graph[i].end();it++)
				for(int j=1;j<=n;j++)
					maxi(f[k][i][j],w[i]+rho[1]*f[k-1][*it][j]);
	}
	for(int i=1;i<=n;i++){
		db val=w[i];
		for(int k=1;k<=n;k++)
			maxi(val,f[k][i][i]/(1-rho[k]));
		for(int k=0;k<=n;k++)
			maxi(ans,f[k][v0][i]+rho[k]*val);
	}
	printf("%.1lf\n",ans);
}

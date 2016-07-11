#include <cstdio>
typedef long long ll;
const int N=105,inf=(int)1e9+7;
int n,m,g[N][N],dist[N][N],deg[N],head,tail,q[N];
ll c[N][N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j) g[i][j]=inf;
	while(m--){
		int a,b,c; scanf("%d%d%d",&a,&b,&c);
		g[a][b]=g[b][a]=c;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dist[i][j]=g[i][j];
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++) if(k!=j)
				if(dist[i][k]+g[k][j]==dist[i][j])
					deg[j]++;
		head=tail=0;
		q[tail++]=i;
		c[i][i]=1;
		while(head<tail){
			int u=q[head++];
			for(int v=1;v<=n;v++) if(v!=u&&dist[i][u]+g[u][v]==dist[i][v]){
				c[i][v]+=c[i][u];
				if(!--deg[v]) q[tail++]=v;
			}
		}
	}
	for(int k=1;k<=n;k++){
		double ans=0;
		for(int i=1;i<=n;i++) if(i!=k)
			for(int j=1;j<=n;j++) if(j!=k)
				if(dist[i][k]+dist[k][j]==dist[i][j])
					ans+=1.*c[i][k]*c[k][j]/c[i][j];
		printf("%.3lf\n",ans);
	}
}

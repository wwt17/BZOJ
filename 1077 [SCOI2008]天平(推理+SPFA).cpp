#include <cstdio>
#include <queue>
using namespace std;
const int N=55;
int n,a,b,c1,c2,c3,low[8]={0,0,1,1,3,3,3,3},high[8]={0,6,4,6,0,6,4,6},val[8]={0,0,1,1,2,2,2,2};
char g[N][N];
int f[N],ff[N][N];
bool inq[N];
queue<int> q;
int c[4];
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%s",g[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(g[i][j]=='+') g[i][j]='>'; else
			if(g[i][j]=='-') g[i][j]='<';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(g[i][j]=='?'&&g[j][i]!='?')
				g[i][j]=g[j][i]=='<'?'>':g[j][i]=='>'?'<':'=';
	for(int ka=0;ka<3;ka++)
		for(int kb=0;kb<3;kb++)
			for(int i=1;i<=n;i++) if(i!=a&&i!=b)
				for(int ki=0;ki<3;ki++){
					for(int j=1;j<=n;j++) f[j]=7;
					f[a]=1<<ka;
					f[b]=1<<kb;
					f[i]=1<<ki;
					for(int j=1;j<=n;j++) q.push(j),inq[j]=1;
					while(!q.empty()){
						int u=q.front(); q.pop(); inq[u]=0;
						for(int v=1;v<=n;v++) if(g[v][u]!='?'){
							int t=0;
							if(g[v][u]=='>') t=high[f[u]]; else
							if(g[v][u]=='<') t=low[f[u]]; else
							t=f[u];
							if((f[v]&t)!=f[v]){
								f[v]&=t;
								if(!inq[v])
									q.push(v),inq[v]=1;
							}
						}
					}
					bool ok=1;
					for(int j=1;j<=n;j++) if(!f[j]){
						ok=0;
						break;
					}
					if(!ok) continue;
					for(int j=i+1;j<=n;j++) if(j!=a&&j!=b&&j!=i)
						for(int k=0;k<3;k++) if(f[j]>>k&1){
							int t=val[f[i]]+val[1<<k]-val[f[a]]-val[f[b]];
							if(t<0){
								if(ff[i][j]==0) ff[i][j]=1; else
								if(ff[i][j]!=1) ff[i][j]=-1;
							}
							else
							if(t==0){
								if(ff[i][j]==0) ff[i][j]=2; else
								if(ff[i][j]!=2) ff[i][j]=-1;
							}
							else{
								if(ff[i][j]==0) ff[i][j]=3; else
								if(ff[i][j]!=3) ff[i][j]=-1;
							}
						}
				}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(ff[i][j]>0){
				c[ff[i][j]]++;
			}
	printf("%d %d %d\n",c[1],c[2],c[3]);
}

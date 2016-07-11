#include <cstdio>
#include <queue>
using namespace std;
const int S=50,N=50;
int s,m;
struct atma{
	int n,p[N][2];
	bool out[N];
	void read(){
		int m;
		scanf("%d%d",&n,&m);
		while(m--){
			int x; scanf("%d",&x);
			out[x]=1;
		}
		for(int i=0;i<n;i++) scanf("%d%d",&p[i][0],&p[i][1]);
	}
} a[S];
int tim,f[N][N];
void dfs(int i,int j,int x,int y){
	if(f[x][y]==tim) return;
	f[x][y]=tim;
	dfs(i,j,a[i].p[x][0],a[j].p[y][0]);
	dfs(i,j,a[i].p[x][1],a[j].p[y][1]);
}
int len,dfn[S],low[S],cnt[S],top,stack[S],belong[S];
bool instack[S],g[S][S],h[S][S];
void tarjan(int u){
	dfn[u]=low[u]=++len;
	stack[top++]=u;
	instack[u]=1;
	for(int v=0;v<s;v++) if(g[u][v]){
		if(instack[v]){
			if(dfn[v]<low[u]) low[u]=dfn[v];
		}
		else
		if(!dfn[v]){
			tarjan(v);
			if(low[v]<low[u]) low[u]=low[v];
		}
	}
	if(low[u]==dfn[u]){
		do{
			int v=stack[--top];
			belong[v]=m;
			cnt[m]++;
			instack[v]=0;
		}
		while(stack[top]!=u);
		m++;
	}
}
int d[S];
queue<int> q;
int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&s);
	for(int i=0;i<s;i++) a[i].read();
	for(int i=0;i<s;i++)
		for(int j=0;j<s;j++){
			tim++;
			dfs(i,j,0,0);
			bool ok=1;
			for(int x=0;x<a[i].n&&ok;x++) if(!a[i].out[x])
				for(int y=0;y<a[j].n&&ok;y++) if(a[j].out[y])
					if(f[x][y]==tim) ok=0;
			g[i][j]=ok;
		}
	for(int i=0;i<s;i++) if(!dfn[i])
		tarjan(i);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			f[i][j]=0;
	for(int i=0;i<s;i++)
		for(int j=0;j<s;j++) if(g[i][j])
			f[belong[i]][belong[j]]=1;
	for(int i=0;i<m;i++) f[i][i]=0;
	int ans=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++) d[j]=0;
		q.push(i);
		d[i]=cnt[i];
		while(!q.empty()){
			int u=q.front(); q.pop();
			if(d[u]>ans) ans=d[u];
			for(int v=0;v<m;v++) if(f[u][v])
				if(d[u]+cnt[v]>d[v]){
					d[v]=d[u]+cnt[v];
					q.push(v);
				}
		}
	}
	printf("%d\n",ans);
	scanf("\n");
}

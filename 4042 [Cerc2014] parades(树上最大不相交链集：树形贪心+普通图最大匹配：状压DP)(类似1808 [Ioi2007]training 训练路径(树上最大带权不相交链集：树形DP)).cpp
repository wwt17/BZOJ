#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1005,D=10;

int n;

int newE;
int ed[N<<1],next[N<<1],son[N];
int lis[N][N];
bool g[N][N],link[D][D];
int lg[1<<D],f[1<<D];

int dfs(int u,int fa=0){
	int ans=0;
	int d=0;
	int s[10];
	for(int e=son[u];e;e=next[e]){
		int v=ed[e];
		if(v==fa) continue;
		ans+=dfs(v,u);
		for(int i=1;i<=*lis[v];i++) if(g[lis[v][i]][u])
			ans++,*lis[v]=0;
		s[d++]=v;
	}
	for(int x=0;x<d;x++) for(int y=x+1;y<d;y++){
		link[x][y]=false;
		for(int i=1;i<=*lis[s[x]];i++) for(int j=1;j<=*lis[s[y]];j++) if(g[lis[s[x]][i]][lis[s[y]][j]]){
			link[x][y]=true;
			goto out;
		}
		out:;
	}
	f[0]=0;
	for(int s=1;s<1<<d;s++){
		f[s]=f[s^(s&-s)];
		int x=lg[s&-s];
		for(int y=x+1;y<d;y++) if((s>>y&1)&&link[x][y])
			f[s]=max(f[s],f[s^(1<<x)^(1<<y)]+1);
	}
	ans+=f[(1<<d)-1];
	*lis[u]=1;
	lis[u][1]=u;
	for(int x=0;x<d;x++) if(f[((1<<d)-1)^(1<<x)]==f[(1<<d)-1]){
		for(int i=1;i<=*lis[s[x]];i++) lis[u][++*lis[u]]=lis[s[x]][i];
	}
	return ans;
}

int Main(){
	scanf("%d",&n);
	newE=2;
	for(int i=1;i<=n;i++) son[i]=0;
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		ed[newE]=y,next[newE]=son[x],son[x]=newE++;
		ed[newE]=x,next[newE]=son[y],son[y]=newE++;
	}
	int m; scanf("%d",&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) g[i][j]=false;
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		g[x][y]=g[y][x]=true;
	}
	return dfs(1);
}

int main(){
	for(int i=0;i<D;i++) lg[1<<i]=i;
	int T; scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
		printf("%d\n",Main());
}

#include <cstdio>
#include <algorithm>
using namespace std;

const int N=110,mo=(int)1e9+7;

int n,mm,m;
int x[N],y[N];
int id[N];
int belong[N];
int get(int x){
	if(!belong[x]) return x;
	return belong[x]=get(belong[x]);
}

int fa[N],son[N],nex[N];
int vis[N];

int size[N],f[N][N],ff[N],g[N][N][N];

void dp(int u){
	size[u]=0;
	f[u][0]=1;
	for(int v=son[u];v;v=nex[v]){
		dp(v);
		for(int k=0;k<=size[u]+size[v];k++) ff[k]=0;
		for(int i=0;i<=size[u];i++)
			for(int j=0;j<=size[v];j++)
				for(int k=max(i,j);k<=i+j;k++)
					ff[k]=(ff[k]+1LL*f[u][i]*f[v][j]%mo*g[i][j][k])%mo;
		size[u]+=size[v];
		for(int k=0;k<=size[u];k++) f[u][k]=ff[k];
	}
	for(int i=size[u];i>=0;i--) f[u][i+1]=f[u][i];
	size[u]++;
	f[u][0]=0;
}

int main(){
	scanf("%d%d",&n,&mm);
	while(mm--){
		int x,y; char c;
		scanf("%d",&x);
		while((c=getchar())!='<'&&c!='=');
		scanf("%d",&y);
		if(c=='='){
			int xx=get(x),yy=get(y);
			if(xx!=yy)
				belong[yy]=xx;
		}
		else{
			++m;
			::x[m]=x;
			::y[m]=y;
		}
	}
	int nn=0;
	for(int i=1;i<=n;i++) if(!belong[i]) id[i]=++nn;
	for(int i=1;i<=m;i++){
		fa[id[get(y[i])]]=id[get(x[i])];
	}
	n=nn;
	for(int i=1;i<=n;i++){
		int j;
		for(j=i;vis[j]!=i;j=fa[j]) vis[j]=i;
		if(j){
			puts("0");
			return 0;
		}
	}
	++n;
	for(int i=1;i<n;i++){
		if(!fa[i]) fa[i]=n;
		nex[i]=son[fa[i]];
		son[fa[i]]=i;
	}
	for(int i=0;i<=n;i++)
		for(int j=0;i+j<=n;j++)
			for(int k=max(i,j);k<=i+j;k++){
				if(!i||!j){
					g[i][j][k]=1;
					continue;
				}
				g[i][j][k]=((g[i-1][j][k-1]+g[i][j-1][k-1])%mo+g[i-1][j-1][k-1])%mo;
			}
	dp(n);
	int ans=0;
	for(int j=0;j<=n;j++) ans=(ans+f[n][j])%mo;
	printf("%d\n",ans);
}

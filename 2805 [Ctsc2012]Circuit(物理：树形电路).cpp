#include <cstdio>
#include <algorithm>
using namespace std;
typedef double real;

const int N=50005;

int n,newE=2;
int son[N],ed[N<<1],next[N<<1],fa[N],d[N];
real k[N],b[N],U[N];

void addedge(int u,int v){
	ed[newE]=v,next[newE]=son[u],son[u]=newE++,d[u]++;
	ed[newE]=u,next[newE]=son[v],son[v]=newE++,d[v]++;
}

void dfs(int u){
	if(u!=0&&d[u]==1){
		k[u]=1./2;
		b[u]=-U[u]/2;
		return;
	}
	k[u]=d[u];
	b[u]=-U[u];
	for(int e=son[u];e;e=next[e]){
		int v=ed[e];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
		k[u]-=k[v];
		b[u]+=b[v]+U[v];
	}
	k[u]=1/k[u];
	b[u]*=k[u];
}

real phi(int u){
	if(u==0) return 0;
	return k[u]*phi(fa[u])+b[u];
}

int main(){
	int m; scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v; scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	for(int i=1;i<=n;i++) if(d[i]==1){
		addedge(0,i);
		break;
	}
	dfs(0);
	while(m--){
		char opt=getchar();
		if(opt=='C'){
			int u,v; real w; scanf("%d%d%lf",&u,&v,&w);
			if(fa[u]==v) swap(u,v); else w*=-1;
			U[v]+=w;
			b[v]-=w*k[v];
			real delta=w-w*k[v];
			for(;u;u=fa[u])
				b[u]+=delta*=k[u];
		}
		else
		if(opt=='Q'){
			int u; scanf("%d",&u);
			printf("%.10lf\n",phi(u));
		}
		else
			m++;
	}
}

#include <cstdio>
#include <algorithm>
using namespace std;

const int N=105,M=1005,inf=(int)1e9+7;

int n,m;

int lx[N],ly[M],w[N][M];

int my[M];

bool visx[N],visy[M];

bool extend(int u){
	if(!u) return true;
	visx[u]=true;
	for(int v=1;v<=m;v++) if(!visy[v]&&lx[u]+ly[v]==w[u][v]){
		visy[v]=true;
		if(extend(my[v])){
			my[v]=u;
			return true;
		}
	}
	return false;
}

int KM(){
	for(int i=1;i<=n;i++){
		lx[i]=-inf;
		for(int j=1;j<=m;j++) lx[i]=max(lx[i],w[i][j]);
	}
	for(int j=1;j<=m;j++){
		ly[j]=0;
		my[j]=0;
	}
	for(int u=1;u<=n;u++)
		while(true){
			for(int i=1;i<=n;i++) visx[i]=false;
			for(int j=1;j<=m;j++) visy[j]=false;
			if(extend(u)) break;
			int delta=inf;
			for(int i=1;i<=n;i++) if(visx[i])
				for(int j=1;j<=m;j++) if(!visy[j])
					delta=min(delta,lx[i]+ly[j]-w[i][j]);
			for(int i=1;i<=n;i++) if(visx[i]) lx[i]-=delta;
			for(int j=1;j<=m;j++) if(visy[j]) ly[j]+=delta;
		}
	int ans=0;
	for(int j=1;j<=m;j++) if(my[j]) ans+=w[my[j]][j];
	return ans;
}

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E+2;
int we[M];
bool ontree[M];
struct node{
	edge *son,*pre;
	int depth;
	void dfs(){
		for(edge *e=son;e;e=e->next) if(!e->ed->depth&&ontree[e-E>>1]){
			e->ed->pre=E+(e-E^1);
			e->ed->depth=depth+1;
			e->ed->dfs();
		}
	}
} V[N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d%d",&x,&y,&we[i]);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		for(edge *e=V[x].son;e;e=e->next) if(e->ed==V+y){
			ontree[e-E>>1]=true;
			break;
		}
	}
	V[n].depth=1;
	V[n].dfs();
	for(int i=1;i<=m;i++) if(!ontree[i]){
		node *u=E[i<<1|1].ed,*v=E[i<<1].ed;
		while(u!=v){
			if(u->depth<v->depth) swap(u,v);
			w[u-V][i]=max(0,we[u->pre-E>>1]-we[i]);
			u=u->pre->ed;
		}
	}
	n--;
	printf("%d\n",KM());
}

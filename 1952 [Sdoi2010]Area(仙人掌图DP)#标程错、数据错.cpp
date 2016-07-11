#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1000005,M=2000005,inf=(int)2e9+7;
int n,m;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	node *next;
	int dfn,low;
	int w;
	int f[3],g[3];
	void tarjan(node *fa){
		static int len=0;
		dfn=low=++len;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==fa) continue;
			if(v->dfn){
				if(v->dfn<=low){
					low=v->dfn;
					next=v;
				}
				continue;
			}
			v->tarjan(this);
			if(v->low<=low){
				low=v->low;
				next=v;
			}
		}
		g[0]=w;
		g[1]=0;
		g[2]=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=next&&e->ed!=fa)
			g[0]+=e->ed->f[2],
			g[1]+=e->ed->f[0],
			g[2]+=e->ed->f[1];
		g[1]=max(g[1],g[2]);
		g[0]=max(g[0],g[1]);
		if(low==dfn){
			if(!next){
				f[0]=g[0];
				f[1]=g[1];
				f[2]=g[2];
				return;
			}
			int x[3],y[3];
			
			x[0]=g[0];
			x[1]=-inf;
			x[2]=-inf;
			for(node *u=next;u!=this;u=u->next){
				y[0]=u->g[0]+x[2];
				y[1]=u->g[1]+x[0];
				y[2]=u->g[2]+x[1];
				y[1]=max(y[1],y[2]);
				y[0]=max(y[0],y[1]);
				x[0]=y[0];
				x[1]=y[1];
				x[2]=y[2];
			}
			f[0]=x[2];
			
			x[0]=g[1];
			x[1]=g[1];
			x[2]=g[1];
			for(node *u=next;u!=this;u=u->next){
				y[0]=u->g[0]+x[2];
				y[1]=u->g[1]+x[0];
				y[2]=u->g[2]+x[1];
				y[1]=max(y[1],y[2]);
				y[0]=max(y[0],y[1]);
				x[0]=y[0];
				x[1]=y[1];
				x[2]=y[2];
			}
			f[1]=x[0];
			
			x[0]=g[2];
			x[1]=g[2];
			x[2]=-inf;
			for(node *u=next;u!=this;u=u->next){
				y[0]=u->g[0]+x[2];
				y[1]=u->g[1]+x[0];
				y[2]=u->g[2]+x[1];
				y[1]=max(y[1],y[2]);
				y[0]=max(y[0],y[1]);
				x[0]=y[0];
				x[1]=y[1];
				x[2]=y[2];
			}
			f[2]=x[1];
			
			f[1]=max(f[1],f[2]);
			f[0]=max(f[0],f[1]);
		}
	}
} V[N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].w);
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	int ans=0;
	for(int i=1;i<=n;i++) if(!V[i].dfn){
		V[i].tarjan(NULL);
		ans+=V[i].f[0];
	}
	printf("%d\n",ans);
	scanf("\n");
}

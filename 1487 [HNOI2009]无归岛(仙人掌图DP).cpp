#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005,M=200005,inf=N*1000*3;
int n,m,len;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	node *next;
	int low,dfn;
	int a,f0,f1;
	void tarjan(node *fa){
		low=dfn=++len;
		f1=a;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==fa) continue;
			if(v->dfn){
				if(v->dfn<low){
					low=v->dfn;
					next=v;
				}
				continue;
			}
			v->tarjan(this);
			if(v->low==dfn){
				int g0=0,g1=-inf;
				for(node *u=v;u!=this;u=u->next){
					int gg0=max(g0,g1)+u->f0,gg1=g0+u->f1;
					g0=gg0,g1=gg1;
				}
				f0+=max(g0,g1);
				g0=-inf,g1=0;
				for(node *u=v;u!=this;u=u->next){
					int gg0=max(g0,g1)+u->f0,gg1=g0+u->f1;
					g0=gg0,g1=gg1;
				}
				f1+=g0;
			}
			else
				if(v->low<low){
					low=v->low;
					next=v;
				}
		}
		f1=max(0,f1);
	}
} V[N];

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int i=1;i<=n;i++) scanf("%d",&V[i].a);
	V[1].tarjan(NULL);
	printf("%d\n",max(V[1].f0,V[1].f1));
}

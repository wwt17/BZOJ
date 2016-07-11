#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int N=200000;
int n;
struct node;
typedef pair<int,int> pii;
map<pii,node*> h;
struct edge{
	node *ed;
	edge *next;
} E[N<<3],*newE=E;
struct node{
	edge *son; int depth;
	void dfs(node *from){
		for(edge *e=son;e;e=e->next) if(e->ed!=from){
			e->ed->depth=depth+1;
			e->ed->dfs(this);
		}
	}
} V[N];
inline void add(node *u,int a,int b){
	if(a>b) swap(a,b);
	map<pii,node*>::iterator it=h.find(pii(a,b));
	if(it==h.end())
		h[pii(a,b)]=u;
	else{
		node *v=h[pii(a,b)];
		*newE=(edge){v,u->son},u->son=newE++;
		*newE=(edge){u,v->son},v->son=newE++;
	}
}
int main(){
	scanf("%d",&n);
	for(node *u=V;u<V+(n-2);u++){
		static int p,q,r; scanf("%d%d%d",&p,&q,&r);
		add(u,p,q);
		add(u,p,r);
		add(u,q,r);
	}
	V->depth=1;
	V->dfs(NULL);
	node *best=V;
	for(node *u=V;u<V+(n-2);u++) if(u->depth>best->depth)
		best=u;
	best->depth=1;
	best->dfs(NULL);
	int ans=0;
	for(node *u=V;u<V+(n-2);u++) if(u->depth>ans)
		ans=u->depth;
	printf("%d\n",ans);
	scanf("\n");
}

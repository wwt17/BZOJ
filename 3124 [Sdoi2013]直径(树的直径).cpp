#include <cstdio>
const int N=200005;
typedef long long ll;
int n,cnt;
ll ans;

struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	node *pa,;
	edge *son,*to;
	ll far;
	void dfs1(){
		far=0;
		to=NULL;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->pa=this;
			v->dfs1();
			ll now=e->w+v->far;
			if(now>far) far=now,to=e;
		}
	}
	ll get(){
		ll ans=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa&&e!=to)
			if(e->w+e->ed->far>ans) ans=e->w+e->ed->far;
		return ans;
	}
} V[N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<n-1;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	V[1].dfs1();
	node *x=V+1;
	for(;x->to;x=x->to->ed);
	x->pa=NULL;
	x->dfs1();
	printf("%lld\n",x->far);
	node *y=x;
	for(;y->to;y=y->to->ed);
	node *i=x;
	for(;i->get()!=i->far;i=i->to->ed);
	y->pa=NULL;
	y->dfs1();
	for(;i->get()!=i->far;i=i->to->ed) cnt++;
	printf("%d\n",cnt);
}

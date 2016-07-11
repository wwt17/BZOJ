#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=(int)1e5+5,logN=19;

int n;

struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *fa;
	node *hea,*nex,*t;
	int dist[logN];
	int level;
	int sz;
	int w;
	ll sum,val,sum_,val_;
} *root,V[N];

int dfs(node *u,node *from,int d,int level){
	if(u->level<level) return 0;
	u->sz=1;
	u->dist[level]=d;
	for(edge *e=u->son;e;e=e->next) if(e->ed!=from)
		u->sz+=dfs(e->ed,u,d+e->w,level);
	return u->sz;
}

node* getroot(node *u,int level){
	for(;;){
		bool moved=false;
		for(edge *e=u->son;e;e=e->next) if(e->ed->level>=level&&e->ed->sz*2>u->sz){
			int tmp=u->sz;
			u->sz-=e->ed->sz;
			e->ed->sz=tmp;
			u=e->ed;
			moved=true;
			break;
		}
		if(!moved) return u;
	}
}

node* dianfen(node *u,node *fa,int level){
	dfs(u,NULL,0,level);
	u=getroot(u,level);
	u->level=level;
	u->fa=fa;
	dfs(u,NULL,0,level);
	u->hea=NULL;
	for(edge *e=u->son;e;e=e->next) if(e->ed->level>=level){
		node *v=dianfen(e->ed,u,level+1);
		v->nex=u->hea;
		u->hea=v;
		v->t=e->ed;
	}
	return u;
}

void modify(node *u,int d){
	for(node *v=u;v;v=v->fa){
		v->sum+=d;
		v->val+=1LL*d*u->dist[v->level];
		if(v->fa){
			v->sum_+=d;
			v->val_+=1LL*d*u->dist[v->level-1];
		}
	}
}

ll calc(node *u){
	ll ans=0;
	for(node *v=u;v;v=v->fa){
		ans+=v->val+v->sum*u->dist[v->level];
		if(v->fa){
			ans-=v->val_+v->sum_*u->dist[v->level-1];
		}
	}
	return ans;
}

ll query(node *u){
	ll tmp=calc(u);
	for(node *v=u->hea;v;v=v->nex){
		if(calc(v->t)<tmp)
			return query(v);
	}
	return tmp;
}

int main(){
	int q; scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	for(int i=1;i<=n;i++) V[i].level=logN;
	root=dianfen(V+1,NULL,0);
	while(q--){
		int x,d; scanf("%d%d",&x,&d);
		modify(V+x,d);
		printf("%lld\n",query(root));
	}
}

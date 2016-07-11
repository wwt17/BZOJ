#include <cstdio>
#include <algorithm>
using namespace std;

const int N=2e5+5,logN=18,M=5e5+5;

inline int getint(){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return f?-a:a;
}

int n,m,len;
int lg[N];

struct node *seq[N];
struct edge{
	node *ed;
	edge *next;
} E[M+M+N+N],*newE=E;
struct node{
	edge *pre,*suc,*dom;
	node *from,*semi,*idom;
	int dfn;
	node *belong,*best;
	node *get(){
		if(!belong) return this;
		node *t=belong->get();
		if(belong->best->semi->dfn<best->semi->dfn)
			best=belong->best;
		return t;
	}
	void dfsdfn(){
		seq[dfn=++len]=this;
		for(edge *e=suc;e;e=e->next) if(!e->ed->dfn){
			e->ed->from=this;
			e->ed->dfsdfn();
		}
	}
	node *pa[logN];
	int depth;
	int mi;
	int live;
	void dfsdom(){
		pa[0]=idom;
		for(int j=1;j<=lg[depth];j++) pa[j]=pa[j-1]->pa[j-1];
		for(edge *e=dom;e;e=e->next){
			e->ed->depth=depth+1;
			e->ed->mi=min(e->ed->mi,mi);
			e->ed->dfsdom();
		}
	}
} V[N],*r;

node *lca(node *u,node *v){
	while(u->depth>v->depth) u=u->pa[lg[u->depth-v->depth]];
	while(v->depth>u->depth) v=v->pa[lg[v->depth-u->depth]];
	if(u==v) return u;
	for(int j=lg[u->depth];j>=0;j--) if(u->pa[j]!=v->pa[j]) u=u->pa[j],v=v->pa[j];
	return u->pa[0];
}

inline void addedge(edge *&son,node *ed){
	*newE=(edge){ed,son},son=newE++;
}

void tarjan(){
	for(int i=1;i<=len;i++){
		node *u=seq[i];
		u->semi=u->best=u;
	}
	for(int i=len;i>=2;i--){
		node *u=seq[i];
		for(edge *e=u->pre;e;e=e->next){
			node *v=e->ed;
			if(!v->dfn) continue;
			v->get();
			if(v->best->semi->dfn<u->semi->dfn)
				u->semi=v->best->semi;
		}
		addedge(u->semi->dom,u);
		u->belong=u->from;
		u=u->from;
		for(edge *e=u->dom;e;e=e->next){
			node *v=e->ed;
			v->get();
			if(v->semi==v->best->semi)
				v->idom=v->semi;
			else
				v->idom=v->best;
		}
		u->dom=NULL;
	}
	for(int i=2;i<=len;i++){
		node *u=seq[i];
		if(u->idom!=u->semi)
			u->idom=u->idom->idom;
		addedge(u->idom->dom,u);
	}
}

int main(){
	n=getint(),m=getint(),r=V+getint();
	lg[1]=0;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	while(m--){
		node *u=V+getint(),*v=V+getint();
		addedge(u->suc,v);
		addedge(v->pre,u);
	}
	r->dfsdfn();
	tarjan();
	for(int i=1;i<=n;i++) V[i].mi=getint();
	r->dfsdom();
	int q=getint();
	for(int tim=1;tim<=q;tim++){
		int k=getint(),w=getint();
		node *t=NULL;
		while(k--){
			node *u=V+getint();
			u->live=tim;
			if(u->dfn){
				if(t) t=lca(t,u); else t=u;
			}
		}
		int ans=t?(t->live==tim?t->idom:t)->mi:0;
		if(w>=ans)
			printf("%d\n",ans);
		else
			puts("1");
	}
}

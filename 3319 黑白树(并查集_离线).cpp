#include <cstdio>
const int N=1000001,M=1000001;
int n,m;
struct node;
struct edge{
	node *ed; edge *next;
} E[N<<1],*newE=E+2;
struct node{
	edge *son,*above; node *pa,*v; int depth;
	void build(){
		v=this;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->above=e;
			e->ed->depth=depth+1;
			e->ed->build();
		}
	}
	void rebuild(){
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			if(e->ed->v==e->ed)
				e->ed->v=v;
			else
				e->ed->v=e->ed;
			e->ed->rebuild();
		}
	}
	node *get(){
		if(v==this) return this;
		return v=v->get();
	}
} V[N];
node *ord[N],**top=ord;
struct query{
	node *u,**p,*ans;
} q[M],*newq=q;
int main(){
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	V[1].build();
	int kind;
	while(m--)
		if(scanf("%d",&kind),kind==1){
			scanf("%d",&a);
			newq->u=V+a;
			newq->p=top;
			newq++;
		}
		else{
			scanf("%d%d",&a,&b);
			for(node *u=V[a].get(),*v=V[b].get();u!=v;)
				if(u->depth>v->depth){
					*top++=u;
					u->v=u->pa;
					u=u->get();
				}
				else{
					*top++=v;
					v->v=v->pa;
					v=v->get();
				}
		}
	V[0].v=V;
	V[0].above=E;
	V[1].v=V;
	V[1].rebuild();
	for(query *cur=newq;cur-->q;){
		while(top>cur->p){
			node *u=*--top;
			u->v=u->pa;
		}
		cur->ans=cur->u->get();
	}
	for(query *cur=q;cur<newq;cur++)
		printf("%d\n",(cur->ans->above-E)>>1);
}

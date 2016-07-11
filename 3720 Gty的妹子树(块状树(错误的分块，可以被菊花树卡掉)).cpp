#include <cstdio>
#include <algorithm>
using namespace std;

const int N=60005,S=1000,B=10005;

int n;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct block{
	int size;
	node *a[S];
	int w[S];
	block *son,*next;
	void addson(block *b2){
		b2->next=son;
		son=b2;
	}
	void rebuild();
} b[B],*newblock=b;

struct node{
	node *pa;
	edge *son;
	int w;
	block *belong;
	void buildblock(block *b){
		belong=b;
		belong->a[belong->size++]=this;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==pa) continue;
			v->pa=this;
			if(belong->size<S)
				v->buildblock(belong);
			else{
				block *nb=newblock++;
				b->addson(nb);
				v->buildblock(nb);
			}
		}
	}
} V[N];
void block::rebuild(){
	for(int i=0;i<size;i++) w[i]=a[i]->w;
	sort(w,w+size);
}
void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++;
	*newE=(edge){u,v->son},v->son=newE++;
}

int query(block *u,int x){
	int ret=u->size-(upper_bound(u->w,u->w+u->size,x)-u->w);
	for(block *v=u->son;v;v=v->next)
		ret+=query(v,x);
	return ret;
}

int query(node *u,int x){
	int ret=u->w>x;
	for(edge *e=u->son;e;e=e->next){
		node *v=e->ed;
		if(v==u->pa) continue;
		if(v->belong==u->belong)
			ret+=query(v,x);
		else
			ret+=query(v->belong,x);
	}
	return ret;
}

void modify(node *u,int x){
	u->w=x;
	u->belong->rebuild();
}

void addnode(node *pa,int x){
	node *u=V+(++n);
	addedge(pa,u);
	u->pa=pa;
	u->w=x;
	if(pa->belong->size<S)
		u->belong=pa->belong;
	else{
		u->belong=newblock++;
		pa->belong->addson(u->belong);
	}
	u->belong->a[u->belong->size++]=u;
	u->belong->rebuild();
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		addedge(V+x,V+y);
	}
	for(int i=1;i<=n;i++) scanf("%d",&V[i].w);
	V[1].buildblock(newblock++);
	for(block *cur=b;cur<newblock;cur++) cur->rebuild();
	int m; scanf("%d",&m);
	int ans=0;
	while(m--){
		int type,u,x; scanf("%d%d%d",&type,&u,&x); u^=ans,x^=ans;
		if(type==0)
			printf("%d\n",ans=query(V+u,x));
		else
		if(type==1)
			modify(V+u,x);
		else
		if(type==2)
			addnode(V+u,x);
	}
}

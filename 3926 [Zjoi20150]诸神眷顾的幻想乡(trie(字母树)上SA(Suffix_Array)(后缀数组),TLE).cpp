#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=200005,logN=18,M=20;

int n,ch,logn,maxdep;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	int c;
	int deg;
} V[N];

void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++; u->deg++;
	*newE=(edge){u,v->son},v->son=newE++; v->deg++;
}

struct trie{
	trie *pa[logN],*son,*next;
	int rank,trank,height;
	char c;
	trie* ac(int x){
		trie *v=this;
		for(int lev=0;x>>lev;lev++) if(x>>lev&1) v=v->pa[lev];
		return v;
	}
} mem[N*M],*trietop=mem,*root;

void build(trie *cur,node *u,node *fa,int depth=0){
	if(depth>maxdep) maxdep=depth;
	trie *p;
	for(p=cur->son;p;p=p->next) if(p->c==u->c) break;
	if(!p){
		p=trietop++;
		p->c=u->c;
		p->next=cur->son;
		cur->son=p;
		*p->pa=cur;
	}
	for(edge *e=u->son;e;e=e->next) if(e->ed!=fa)
		build(p,e->ed,u,depth+1);
}

void getpa(trie *cur){
	for(int lev=1;lev<logn;lev++) cur->pa[lev]=cur->pa[lev-1]->pa[lev-1];
	for(trie *p=cur->son;p;p=p->next) getpa(p);
}

trie *sa[N*M];

int sum[N*M];
trie *tmp[N*M];
int key[N*M];
void da(){
	for(int i=0;i<=ch;i++) sum[i]=0;
	for(int i=0;i<=n;i++) sum[mem[i].c]++;
	for(int i=1;i<=ch;i++) sum[i]+=sum[i-1];
	for(int i=n;i>=0;i--) sa[--sum[mem[i].c]]=mem+i;
	int m=0;
	for(int i=0;i<=n;i++)
		sa[i]->rank=i&&sa[i-1]->c==sa[i]->c?m-1:m++;
	for(int lev=0;m<n+1;lev++){
		for(int i=0;i<=m;i++) sum[i]=0;
		for(int i=0;i<=n;i++) sum[key[i]=mem[i].pa[lev]->rank]++;
		for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
		for(int i=n;i>=0;i--) tmp[--sum[key[i]]]=mem+i;
		for(int i=0;i<=m;i++) sum[i]=0;
		for(int i=0;i<=n;i++) sum[key[i]=tmp[i]->rank]++;
		for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
		for(int i=n;i>=0;i--) sa[--sum[key[i]]]=tmp[i];
		m=0;
		for(int i=0;i<=n;i++)
			sa[i]->trank=i&&sa[i-1]->rank==sa[i]->rank&&sa[i-1]->pa[lev]->rank==sa[i]->pa[lev]->rank?m-1:m++;
		for(int i=0;i<=n;i++)
			sa[i]->rank=sa[i]->trank;
	}
}

ll ans;
void getheight(trie *cur=root,int depth=0){
	int h=0;
	for(trie *p=cur->son;p;p=p->next){
		getheight(p,depth+1);
		if(p->height-1>h) h=p->height-1;
	}
	if(cur->rank){
		for(trie *u=sa[cur->rank-1]->ac(h),*v=cur->ac(h);u->c==v->c;u=*u->pa,v=*v->pa)
			h++;
	}
	cur->height=h;
	ans+=depth-h;
}

int main(){
	root=trietop++;
	*root->pa=root;
	scanf("%d%d",&n,&ch);
	for(int i=1;i<=n;i++){
		int c;
		scanf("%d",&c);
		V[i].c=c+1;
	}
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		addedge(V+x,V+y);
	}
	for(int i=1;i<=n;i++) if(V[i].deg==1)
		build(root,V+i,NULL);
	for(logn=0;maxdep>>logn;logn++); logn++;
	getpa(root);
	n=trietop-mem-1;
	da();
	getheight();
	printf("%lld\n",ans);
}

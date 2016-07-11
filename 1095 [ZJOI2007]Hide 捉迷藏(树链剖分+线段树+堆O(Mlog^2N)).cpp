#include <cstdio>
#include <algorithm>
using namespace std;

const int N=100005,inf=N;

int n,cntan;

int memint[N*4*3],*newint=memint;

struct heap{
	int n;
	int *a,*loc,*id;
	heap(int n):n(n){
		a=newint-1; newint+=n;
		loc=newint-1; newint+=n;
		id=newint-1; newint+=n;
		for(int i=1;i<=n;i++) loc[i]=i,id[i]=i;
	}
	void up(int i){
		for(int j;j=i>>1;i=j){
			if(a[id[i]]<=a[id[j]]) break;
			swap(id[i],id[j]);
			loc[id[i]]=i;
			loc[id[j]]=j;
		}
	}
	void down(int i){
		for(int j;(j=i<<1)<=n;i=j){
			if(j+1<=n&&a[id[j+1]]>a[id[j]]) j++;
			if(a[id[i]]>=a[id[j]]) break;
			swap(id[i],id[j]);
			loc[id[i]]=i;
			loc[id[j]]=j;
		}
	}
	void modify(int i,int v){
		a[i]=v;
		up(loc[i]);
		down(loc[i]);
	}
	int top() const{
		return 1>n?-inf:a[id[1]];
	}
	int second_top() const{
		return max(2>n?-inf:a[id[2]],3>n?-inf:a[id[3]]);
	}
} *ans;

struct seg{
	int dl,dr,best;
} memseg[N*4],*newseg=memseg;
int X,D;
struct segtree{
	int n;
	seg *t;
	int inan;
	segtree(int n):n(n){
		t=newseg-1;
		newseg+=n*4;
		inan=++cntan;
	}
	void modify(int cur,int beg,int end){
		if(end-beg==1){
			t[cur].dl=t[cur].dr=t[cur].best=D;
			return;
		}
		int mid=beg+end>>1;
		if(X<=mid)
			modify(cur<<1,beg,mid);
		else
			modify(cur<<1|1,mid,end);
		t[cur].dl=max(t[cur<<1].dl,(mid-beg)+t[cur<<1|1].dl);
		t[cur].dr=max(t[cur<<1|1].dr,(end-mid)+t[cur<<1].dr);
		t[cur].best=max(max(t[cur<<1].best,t[cur<<1|1].best),t[cur<<1].dr+1+t[cur<<1|1].dl);
	}
	seg& top(){
		return t[1];
	}
	void modify(int i,int v){
		X=i; D=v;
		modify(1,0,n);
		ans->modify(inan,t[1].best);
	}
};

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	node *fa;
	edge *son;
	node *prefer;
	int c;
	int size;
	node *top;
	segtree *t;
	heap *h;
	int insg,inhp,inan,a,b;
	void dfs(){
		size=1;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==fa) continue;
			v->fa=this;
			v->dfs();
			size+=v->size;
			if(!prefer||v->size>prefer->size)
				prefer=v;
		}
	}
} V[N];

void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++;
	*newE=(edge){u,v->son},v->son=newE++;
}

void modify(node *u){
	if(u->c^=1)
		u->h->modify(1,0);
	else
		u->h->modify(1,-inf);
	while(u!=V){
		u->a=u->h->top()+u->h->second_top();
		ans->modify(u->inan,u->a);
		u->top->t->modify(u->insg,u->h->top());
		u=u->top;
		u->b=u->t->top().dl;
		if(u->fa!=V)
			u->fa->h->modify(u->inhp,u->b+1);
		u=u->fa;
	}
}

void build(){
	V[1].fa=V;
	V[1].dfs();
	for(node *u=V+1;u<=V+n;u++) if(u->fa->prefer!=u){
		int cnt=0;
		for(node *v=u;v;v=v->prefer){
			v->top=u;
			v->insg=++cnt;
		}
		u->t=new segtree(cnt);
	}
	for(node *u=V+1;u<=V+n;u++){
		int cnt=1;
		for(edge *e=u->son;e;e=e->next) if(e->ed!=u->fa){
			node *v=e->ed;
			if(v==u->prefer) continue;
			v->inhp=++cnt;
		}
		u->h=new heap(cnt);
		u->inan=++cntan;
	}
	ans=new heap(cntan);
	for(node *u=V+1;u<=V+n;u++)
		modify(u);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		addedge(V+x,V+y);
	}
	build();
	int m; scanf("%d",&m);
	while(m--){
		char c=getchar();
		if(c=='C'){
			int x; scanf("%d",&x);
			modify(V+x);
		}
		else
		if(c=='G')
			printf("%d\n",ans->top());
		else
			m++;
	}
}

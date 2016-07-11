#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int N=1e5+5,M=5e5,Q=5e5;
int n,m,q;
struct tree{
	tree *l,*r;
	int sum;
	tree():l(NULL),r(NULL),sum(0){
	}
};
int L[N],*R,*X;
#define findloc(x) lower_bound(L,R,x,greater<int>())
void insert(tree *&a,int *beg,int *end){
	if(!a) a=new tree;
	a->sum++;
	if(end-beg>1){
		int *mid=beg+(end-beg>>1);
		if(X<mid)
			insert(a->l,beg,mid);
		else
			insert(a->r,mid,end);
	}
}
#define sumof(t) (t?t->sum:0)
int *kth(tree *a,int k){
	if(k>sumof(a)) return R;
	int *beg=L,*end=R;
	while(end-beg>1){
		int *mid=beg+(end-beg>>1),mids=sumof(a->l);
		if(k<=mids){
			a=a->l;
			end=mid;
		}
		else{
			k-=mids;
			a=a->r;
			beg=mid;
		}
	}
	return beg;
}
tree *merge(tree *a,tree *b){
	if(!b) return a;
	if(!a) return b;
	a->sum+=b->sum;
	a->l=merge(a->l,b->l);
	a->r=merge(a->r,b->r);
	delete b;
	return a;
}
struct node{
	node *belong;
	tree *t;
	int h;
	void init(){
		belong=this;
		X=findloc(h);
		insert(t,L,R);
	}
	node *get(){
		return belong==this?this:(belong=belong->get());
	}
} V[N];
struct edge{
	node *u,*v; int c;
	bool operator < (const edge &b) const{
		return c<b.c;
	}
	void read(){
		static int a,b;
		scanf("%d%d%d",&a,&b,&c);
		u=V+a; v=V+b;
	}
	void connect(){
		node *x=u->get(),*y=v->get();
		if(x!=y){
			y->belong=x;
			x->t=merge(x->t,y->t);
		}
	}
} E[M];
int ans[Q];
struct query{
	int number; node *v; int x,k;
	bool operator < (const query &b) const{
		return x<b.x;
	}
	void read(){
		static int u;
		scanf("%d%d%d",&u,&x,&k);
		v=V+u;
	}
} seq[Q];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&V[i].h);
		L[i-1]=V[i].h;
	}
	sort(L,L+n,greater<int>());
	R=unique(L,L+n);
	*R=-1;
	for(int i=1;i<=n;i++) V[i].init();
	for(int i=0;i<m;i++) E[i].read();
	sort(E,E+m);
	for(int i=0;i<q;i++){
		seq[i].number=i;
		seq[i].read();
	}
	sort(seq,seq+q);
	for(int i=0,j=0;i<q;i++){
		for(;j<m&&E[j].c<=seq[i].x;j++)
			E[j].connect();
		ans[seq[i].number]=*kth(seq[i].v->get()->t,seq[i].k);
	}
	for(int i=0;i<q;i++) printf("%d\n",ans[i]);
	scanf("\n");
}

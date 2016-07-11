#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
const int N=1e5+5,M=5e5;
#define n1 first
#define n2 second
#define pb push_back
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
	tree *cur=new tree;
	cur->sum=a->sum+b->sum;
	cur->l=merge(a->l,b->l);
	cur->r=merge(a->r,b->r);
	return cur;
}
typedef pair<int,tree*> pit;
struct node{
	node *belong;
	vector<pit> t;
	int h,height,stamp;
	void init(){
		X=findloc(h);
		pit p(0,NULL);
		insert(p.n2,L,R);
		t.pb(p);
	}
	node *get(){
		node *x=this;
		while(x->belong) x=x->belong;
		return x;
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
		if(x==y) return;
		if(x->height<y->height) swap(x,y);
		y->belong=x;
		x->height=max(x->height,y->height+1);
		x->t.pb(pit(c,merge(x->t.rbegin()->n2,y->t.rbegin()->n2)));
		y->stamp=c;
	}
} E[M];
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
	for(int i=0;i<m;i++) E[i].connect();
	int lastans=0,u,x,k;
	while(q--){
		scanf("%d%d%d",&u,&x,&k);
		node *v=V+(u^=lastans);
		x^=lastans;
		k^=lastans;
		while(v->belong&&v->stamp<=x)
			v=v->belong;
		printf("%d\n",lastans=*kth((upper_bound(v->t.begin(),v->t.end(),pit(x,(tree*)0x7fffffff))-1)->n2,k));
		if(lastans==-1) lastans=0;
	}
}

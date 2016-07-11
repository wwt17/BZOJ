#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=300005,M=N;

int n,m;

struct heap{
	heap *l,*r;
	ll val,mul,delta;
	int ans;
	void init(){
		mul=1;
		delta=0;
	}
	void mult(ll x){
		if(!this) return;
		val*=x;
		mul*=x;
		delta*=x;
	}
	void add(ll x){
		if(!this) return;
		val+=x;
		delta+=x;
	}
	void down(){
		if(mul!=1){
			l->mult(mul);
			r->mult(mul);
			mul=1;
		}
		if(delta!=0){
			l->add(delta);
			r->add(delta);
			delta=0;
		}
	}
};

heap *merge(heap *u,heap *v){
	if(!u) return v;
	if(!v) return u;
	if(u->val>v->val) swap(u,v);
	u->down();
	if(rand()&1){
		u->l=merge(u->l,v);
	}
	else{
		u->r=merge(u->r,v);
	}
	return u;
}

heap Q[M];

struct tree{
	tree *son,*next;
	ll h;
	int type;
	ll val;
	int ans;
	heap *lis;
	int depth;
	void getdepth(int d=1){
		depth=d;
		for(tree *v=son;v;v=v->next)
			v->getdepth(d+1);
	}
	heap* dfs();
} V[N];
heap* tree::dfs(){
	heap *res=lis;
	for(tree *v=son;v;v=v->next){
		res=merge(res,v->dfs());
	}
	while(res&&res->val<h){
		ans++;
		res->ans-=depth;
		res->down();
		res=merge(res->l,res->r);
	}
	if(type==1){
		res->mult(val);
	}
	else{
		res->add(val);
	}
	return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&V[i].h);
	for(int i=2;i<=n;i++){
		int f; scanf("%d",&f);
		V[i].next=V[f].son;
		V[f].son=V+i;
		scanf("%d%lld",&V[i].type,&V[i].val);
	}
	V[1].getdepth();
	for(int i=1;i<=m;i++){
		Q[i].init();
		int c; scanf("%lld%d",&Q[i].val,&c);
		Q[i].ans=V[c].depth;
		V[c].lis=merge(V[c].lis,Q+i);
	}
	V[1].dfs();
	for(int i=1;i<=n;i++) printf("%d\n",V[i].ans);
	for(int i=1;i<=m;i++) printf("%d\n",Q[i].ans);
}

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N=50005;
int n,m;

inline ll gcd(const ll a,const ll b){
	return b?gcd(b,a%b):a;
}

struct node *null;
struct node{
	node *l,*r,*pa;
	bool rev;
	int size,a,add;
	ll suml,sumr,sum,ans;
	bool istop(){
		return this==null||pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
		size=l->size+1+r->size;
		suml=l->suml+(l->sum+a)*(1+r->size)+r->suml;
		sumr=r->sumr+(r->sum+a)*(1+l->size)+l->sumr;
		sum=l->sum+a+r->sum;
		ans=l->ans+l->sumr*(r->size+1)+r->suml*(l->size+1)+(ll)a*(l->size+1)*(r->size+1)+r->ans;
	}
	void reverse(){
		if(this==null) return;
		rev^=1;
		swap(l,r);
		swap(suml,sumr);
	}
	void plus(int d){
		if(this==null) return;
		a+=d;
		add+=d;
		suml+=d*(size+1)*size>>1;
		sumr+=d*(size+1)*size>>1;
		sum+=d*size;
		ans+=d*(
			 (ll)(size+1)*(size+1)*size/2
			-(ll)size*(size+1)*(2*size+1)/6
			);
	}
	void down(){
		if(rev){
			l->reverse();
			r->reverse();
			rev=false;
		}
		if(add){
			l->plus(add);
			r->plus(add);
			add=0;
		}
	}
	void correct(){
		if(!istop())
			pa->correct();
		down();
	}
} V[N];

void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	y->l=x->r;
	x->r->pa=y;
	x->r=y;
	y->pa=x;
	y->update();
}
void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	y->r=x->l;
	x->l->pa=y;
	x->l=y;
	y->pa=x;
	y->update();
}
void splay(node *x){
	x->correct();
	while(!x->istop()){
		node *y=x->pa;
		if(y->istop())
			if(x==y->l) zig(x); else zag(x);
		else{
			node *z=y->pa;
			if(y==z->l)
				if(x==y->l) zig(y),zig(x);
				else zag(x),zig(x);
			else
				if(x==y->r) zag(y),zag(x);
				else zig(x),zag(x);
		}
	}
	x->update();
}
node *access(node *x){
	node *y=null;
	while(x!=null){
		splay(x);
		x->r=y;
		x->update();
		y=x;
		x=x->pa;
	}
	return y;
}
node *LCA(node *u,node *v){
	access(u);
	node *lca=access(v);
	return access(u)==lca?lca:null;
}
void cut(node *u,node *v){
	access(u);
	splay(v);
	if(v->pa==u&&v->l==null){
		v->pa=null;
		return;
	}
	access(v);
	splay(u);
	if(u->pa==v&&u->l==null){
		u->pa=null;
		return;
	}
}
/*
void cut(node *u,node *v){
	access(u);
	splay(u);
	u->reverse();
	access(u);
	splay(v);
	if(v->l==null&&v->pa==u){
		v->pa=null;
	}
}
*/
void link(node *u,node *v){
	if(LCA(u,v)!=null) return;
	access(v);
	splay(v);
	v->reverse();
	v->pa=u;
}
void add(node *u,node *v,int d){
	if(LCA(u,v)==null) return;
	access(u);
	splay(u);
	u->reverse();
	access(v)->plus(d);
}
void queryE(node *u,node *v){
	if(LCA(u,v)==null){
		puts("-1");
		return;
	}
	access(u);
	splay(u);
	u->reverse();
	access(v);
	splay(v);
	ll a=v->ans,b=(v->size+1LL)*v->size>>1,g=gcd(a,b);
	printf("%lld/%lld\n",a/g,b/g);
}

int main(){
	null=V;
	null->l=null->r=null->pa=null;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		V[i].l=V[i].r=V[i].pa=null;
		V[i].size=1;
		static int a;
		scanf("%d",&a);
		V[i].plus(a);
	}
	for(int i=1;i<n;i++){
		static int x,y; scanf("%d%d",&x,&y);
		link(V+x,V+y);
	}
	while(m--){
		static int type,x,y,d; scanf("%d%d%d",&type,&x,&y);
		switch(type){
			case 1:
				cut(V+x,V+y);
				break;
			case 2:
				link(V+x,V+y);
				break;
			case 3:
				scanf("%d",&d);
				add(V+x,V+y,d);
				break;
			case 4:
				queryE(V+x,V+y);
				break;
		}
	}
}

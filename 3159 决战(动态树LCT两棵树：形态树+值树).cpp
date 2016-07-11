#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int N=50005,inf=(int)1e9+7;

int n;

struct vbst *vnull;
struct vbst{
	vbst *l,*r,*pa;
	int size,a,delta,ma,mi;
	ll sum;
	bool rev;
	void init(int s){
		l=r=pa=vnull;
		size=s;
	}
	void update(){
		size=l->size+r->size+1;
		sum=l->sum+r->sum+a;
		ma=max(max(l->ma,r->ma),a);
		mi=min(min(l->mi,r->mi),a);
	}
	void reverse(){
		if(this==vnull) return;
		rev^=1;
		swap(l,r);
	}
	void add(int d){
		if(this==vnull) return;
		delta+=d;
		a+=d;
		sum+=1LL*size*d;
		ma+=d;
		mi+=d;
	}
	void down(){
		if(rev){
			l->reverse();
			r->reverse();
			rev=false;
		}
		if(delta){
			l->add(delta);
			r->add(delta);
			delta=0;
		}
	}
	bool istop(){
		return pa==vnull||pa->l!=this&&pa->r!=this;
	}
	void correct(){
		if(!istop()) pa->correct(); down();
	}
	#define x this
	void zig(){
		vbst *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->l=x->r;
		x->r->pa=y;
		x->r=y;
		y->pa=x;
		y->update();
	}
	void zag(){
		vbst *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->r=x->l;
		x->l->pa=y;
		x->l=y;
		y->pa=x;
		y->update();
	}
	#undef x
} V[N];

void splay(vbst *x){
	x->correct();
	while(!x->istop()){
		vbst *y=x->pa;
		if(y->istop())
			if(x==y->l) x->zig(); else x->zag();
		else
			if(y==y->pa->l)
				if(x==y->l)
					y->zig(),x->zig();
				else
					x->zag(),x->zig();
			else
				if(x==y->r)
					y->zag(),x->zag();
				else
					x->zig(),x->zag();
	}
	x->update();
}

vbst* kth(vbst *x,int k){
	for(;;){
		x->down();
		if(k<x->l->size+1)
			x=x->l;
		else
		if(k>x->l->size+1)
			k-=x->l->size+1,x=x->r;
		else
			return x;
	}
}

struct pbst *pnull;
struct pbst{
	pbst *l,*r,*pa;
	int size;
	bool rev;
	vbst *va;
	void init(int s){
		l=r=pa=pnull;
		size=s;
	}
	void update(){
		size=l->size+r->size+1;
	}
	void reverse(){
		if(this==pnull) return;
		rev^=1;
		swap(l,r);
	}
	void down(){
		if(rev){
			l->reverse();
			r->reverse();
			rev=false;
		}
	}
	bool istop(){
		return pa==pnull||pa->l!=this&&pa->r!=this;
	}
	vbst* correct(){
		vbst *res;
		if(!istop())
			res=pa->correct();
		else
			res=va;
		down();
		return res;
	}
	#define x this
	void zig(){
		pbst *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->l=x->r;
		x->r->pa=y;
		x->r=y;
		y->pa=x;
		y->update();
	}
	void zag(){
		pbst *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->r=x->l;
		x->l->pa=y;
		x->l=y;
		y->pa=x;
		y->update();
	}
	#undef x
} P[N];

void splay(pbst *x){
	x->va=x->correct();
	while(!x->istop()){
		pbst *y=x->pa;
		if(y->istop())
			if(x==y->l) x->zig(); else x->zag();
		else
			if(y==y->pa->l)
				if(x==y->l)
					y->zig(),x->zig();
				else
					x->zag(),x->zig();
			else
				if(x==y->r)
					y->zag(),x->zag();
				else
					x->zig(),x->zag();
	}
	x->update();
}

vector<int> g[N];

void build(int u){
	P[u].va=V+u;
	for(int e=0;e<(int)g[u].size();e++){
		int v=g[u][e];
		if(v==P[u].pa-P) continue;
		P[v].pa=P+u;
		build(v);
	}
}

pbst* access(pbst *x){
	pbst *y=pnull;
	while(x!=pnull){
		splay(x);
		vbst *s=kth(x->va,x->l->size+1);
		splay(s);
		x->va=s;
		x->r->va=s->r;
		s->r->pa=vnull;
		s->r=y->va;
		s->r->pa=s;
		s->update();
		x->r=y;
		x->update();
		y=x;
		x=x->pa;
	}
	return y;
}

void makeroot(pbst *u){
	access(u);
	splay(u);
	u->va->reverse();
	u->reverse();
}

int main(){
	freopen("input","r",stdin);
	freopen("out","w",stdout);
	vnull=V; vnull->init(0); vnull->mi=inf;
	pnull=P; pnull->init(0); pnull->va=vnull;
	int m;
	scanf("%d%d%*d",&n,&m);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++) V[i].init(1),P[i].init(1);
	build(1);
	while(m--){
		static char type[100];
		int x,y;
		scanf("%s%d%d",type,&x,&y);
		pbst *u=P+x,*v=P+y;
		makeroot(u);
		access(v);
		splay(v);
		if(type[0]=='I'&&type[2]=='c'){
			int w; scanf("%d",&w);
			v->va->add(w);
		}
		else
		if(type[0]=='S'){
			printf("%lld\n",v->va->sum);
		}
		else
		if(type[0]=='M'&&type[1]=='a'){
			printf("%d\n",v->va->ma);
		}
		else
		if(type[0]=='M'&&type[1]=='i'){
			printf("%d\n",v->va->mi);
		}
		else
		if(type[0]=='I'&&type[1]=='n'){
			v->va->reverse();
		}
		else
			puts("Cannot identify this operation!");
	}
	scanf("\n");
}

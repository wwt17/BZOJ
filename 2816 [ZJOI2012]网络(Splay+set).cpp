#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int N=10005,M=100005,C=10,inf=(int)1e9;
int n,m,c,k;
struct node *null;
struct node{
	node *l,*r,*pa;
	bool rev;
	int w,Max;
	void init(int _w){
		l=r=pa=null;
		Max=w=_w;
	}
	void update(){
		Max=max(w,max(l->Max,r->Max));
	}
	void reverse(){
		rev^=1;
		swap(l,r);
	}
	void down(){
		if(rev){
			l->reverse();
			r->reverse();
			rev=0;
		}
	}
	void correct(){
		if(this!=null) pa->correct(),down();
	}
	void p();
	void ptree();
} V[N][C];
void node::ptree(){
	static int tab=0;
	if(this==null) return;
	tab++;
	l->ptree();
	for(int i=0;i<tab;i++) printf("\t");
	printf("%d ",this-V[0]);
	if(rev) printf("rev");
	puts("");
	r->ptree();
	tab--;
}
void print(){
	puts("-------------print--------------\n");
	for(int j=0;j<c;j++)
		for(int i=1;i<=n;i++)
			if(V[i][j].pa==null)
				V[i][j].ptree(),puts("");
	puts("----------end print-------------");
}
void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else z->r=x;
	x->pa=z;
	y->l=x->r;
	x->r->pa=y;
	x->r=y;
	y->pa=x;
	y->update();
}
void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else z->r=x;
	x->pa=z;
	y->r=x->l;
	x->l->pa=y;
	x->l=y;
	y->pa=x;
	y->update();
}
int splay(node *x,node *top=null){
	node *y,*z;
	x->correct();
	while((y=x->pa)!=top){
		if(y==null)
			return 1;
		if((z=y->pa)==top)
			if(x==y->l) zig(x); else zag(x);
		else{
			if(z==null)
				return 1;
			if(y==z->l)
				if(x==y->l) zig(y),zig(x);
				else zag(x),zig(x);
			else
				if(x==y->r) zag(y),zag(x);
				else zig(x),zag(x);
		}
	}
	x->update();
	return 0;
}
struct edge{
	int x,y,w;
	bool operator < (const edge &b) const{
		return x<b.x||x==b.x&&y<b.y;
	}
	void adjust(){
		if(x>y) swap(x,y);
	}
	int link(){
		node *u=&V[x][w],*v=&V[y][w];
		splay(u);
		if(u->r!=null) u->reverse();
		if(u->r!=null) return 1;
		splay(v);
		if(v->l!=null) v->reverse();
		if(v->l!=null) return 1;
		if(u->pa!=null) return 2;
		u->down();
		u->r=v;
		v->pa=u;
		u->update();
		return 0;
	}
	void cut(){
		node *u=&V[x][w],*v=&V[y][w];
		splay(u);
		splay(v,u);
		v->pa=null;
		if(v==u->l) u->l=null; else u->r=null;
		u->update();
	}
	int query(){
		node *u=&V[x][w],*v=&V[y][w];
		if(u==v)
			return u->w;
		splay(u);
		if(splay(v,u)) return -1;
		int ans=max(u->w,v->w);
		if(v==u->l) ans=max(ans,v->r->Max);
		else ans=max(ans,v->l->Max);
		return ans;
	}
};
set<edge> E;
int main(){
	null=V[0];
	null->l=null->r=null->pa=null;
	null->Max=null->w=-inf;
	scanf("%d%d%d%d",&n,&m,&c,&k);
	for(int i=1;i<=n;i++){
		int w; scanf("%d",&w);
		for(int j=0;j<c;j++) V[i][j].init(w);
	}
	for(int i=0;i<m;i++){
		edge e; scanf("%d%d%d",&e.x,&e.y,&e.w);
		e.adjust();
		e.link();
		E.insert(e);
	}
	while(k--){
		//print();
		int kind,x,w; scanf("%d",&kind);
		set<edge>::iterator it;
		edge e,f;
		switch(kind){
			case 0: scanf("%d%d",&x,&w);
				for(int j=0;j<c;j++){
					node *u=&V[x][j];
					splay(u);
					u->w=w;
					u->update();
				}
				break;
			case 1: scanf("%d%d%d",&e.x,&e.y,&e.w);
				e.adjust();
				it=E.find(e);
				if(it==E.end()){
					puts("No such edge."); break;
				}
				f=*it;
				f.cut();
				switch(e.link()){
					case 1: puts("Error 1."); f.link(); break;
					case 2: puts("Error 2."); f.link(); break;
					case 0: puts("Success."); E.erase(it++); E.insert(it,e); break;
				}
				break;
			case 2: scanf("%d%d%d",&e.w,&e.x,&e.y);
				printf("%d\n",e.query());
				break;
		}
	}
	scanf("\n");
}

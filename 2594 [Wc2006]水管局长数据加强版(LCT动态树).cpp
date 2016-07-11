#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001,M=1000000,Q=100000;
int n,m,q,cnt;

void read(int &a){
	char c;
	while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
void print(int a){
	if(a){ print(a/10); putchar('0'+a%10); }
}

struct node *null;
struct edge{
	node *u,*v; int w; node *to;
	void link();
	void cut();
} E[M],*E2[M];
bool del[M];
struct query{
	node *u,*v; edge *loc; int ans;
} a[Q];

struct node{
	node *l,*r,*pa; bool rev; int w; edge *from;
	node *max,*belong;
	void clear(){
		l=r=pa=null;
		rev=false;
		max=belong=this;
	}
	bool istop(){
		return this==null||pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
		if(l->max->w>r->max->w)
			if(l->max->w>w)
				max=l->max;
			else
				max=this;
		else
			if(r->max->w>w)
				max=r->max;
			else
				max=this;
	}
	void reverse(){
		rev^=1;
		swap(l,r);
	}
	void down(){
		if(rev){
			rev=false;
			l->reverse();
			r->reverse();
		}
	}
	void correct(){
		if(!istop()) pa->correct();
		down();
	}
	node* get(){
		if(belong==this) return this;
		return belong=belong->get();
	}
	void pline();
} V[N];
void zig(node* x){
	node *y=x->pa,*z=y->pa;
	x->pa=z;
	if(z->l==y) z->l=x; else
	if(z->r==y) z->r=x;
	x->r->pa=y;
	y->l=x->r;
	y->pa=x;
	x->r=y;
	y->update();
}
void zag(node* x){
	node *y=x->pa,*z=y->pa;
	x->pa=z;
	if(z->l==y) z->l=x; else
	if(z->r==y) z->r=x;
	x->l->pa=y;
	y->r=x->l;
	y->pa=x;
	x->l=y;
	y->update();
}
void splay(node* x){
	node *y;
	x->correct();
	while(!x->istop())
		if((y=x->pa)->istop())
			if(x==y->l) zig(x); else zag(x);
		else
			if(y==y->pa->l)
				if(x==y->l) zig(y),zig(x);
				else zag(x),zig(x);
			else
				if(x==y->r) zag(y),zag(x);
				else zig(x),zag(x);
	x->update();
}
node* top(node* x){
	splay(x);
	for(;x->l!=null;x=x->l);
	return x;
}
node* access(node* x){
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
bool connected(node* u,node* v){
	return top(access(u))==top(access(v));
}
void link(node* u,node* v){
	access(u);
	splay(u);
	u->reverse();
	u->pa=v;
}
void cut(node* u,node* v){
	access(u);
	splay(v);
	if(v->pa==u){
		v->pa=null;
		return;
	}
	access(v);
	splay(u);
	u->pa=null;
}
node* qmax(node* u,node* v){
	access(u);
	node
		*ansr=access(v)->r->max,
		*ansl=access(u)->r->max;
	return ansl->w>ansr->w?ansl:ansr;
}

void edge::link(){
	to=new node;
	to->clear();
	to->from=this;
	to->w=w;
	::link(to,u);
	::link(to,v);
}
void edge::cut(){
	::cut(to,u);
	::cut(to,v);
	delete to;
}

inline bool cmp(const edge a,const edge b){
	return a.u<b.u||a.u==b.u&&a.v<b.v;
}
inline bool cmpw(const edge* a,const edge* b){
	return a->w<b->w;
}

int main(){
	null=V;
	read(n); read(m); read(q);
	for(int i=0;i<=n;i++) V[i].clear();
	int x,y,k;
	for(int i=0;i<m;i++){
		read(x); read(y); read(E[i].w);
		if(x>y) swap(x,y);
		E[i].u=V+x;
		E[i].v=V+y;
	}
	sort(E,E+m,cmp);
	for(int i=0;i<q;i++){
		read(k); read(x); read(y);
		if(x>y) swap(x,y);
		a[i].u=V+x;
		a[i].v=V+y;
		if(k==2)
			del[(a[i].loc=lower_bound(E,E+m,(edge){a[i].u,a[i].v,0,NULL},cmp))-E]=true;
	}
	//MST
	for(int i=0;i<m;i++) if(!del[i]) E2[cnt++]=E+i;
	sort(E2,E2+cnt,cmpw);
	for(int i=0;i<cnt;i++){
		edge* e=E2[i];
		if(e->u->get()!=e->v->get())
			e->link(),e->v->belong->belong=e->u->belong;
	}
	
	for(int i=q;i--;){
		if(a[i].loc){
			edge* e=a[i].loc;
			if(!connected(e->u,e->v))
				e->link();
			else{
				node* tmp=qmax(e->u,e->v);
				if(tmp->w>e->w){
					tmp->from->cut();
					e->link();
				}
			}
		}
		else
			a[i].ans=connected(a[i].u,a[i].v)
				?qmax(a[i].u,a[i].v)->w:0;
	}
	for(int i=0;i<q;i++) if(!a[i].loc){
		if(a[i].ans) print(a[i].ans);
		else putchar('0');
		putchar('\n');
	}
}

#include <cstdio>
#include <algorithm>
using namespace std;

typedef int Int;
const int inf=0x7fffffff;

int getint(){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return f?-a:a;
}

const int N=100005;

int n;

struct flag{
	Int mul,delta;
	flag(Int _mul=1,Int _delta=0):mul(_mul),delta(_delta){
	}
	void operator += (const flag &b){
		mul*=b.mul;
		delta=delta*b.mul+b.delta;
	}
	void clear(){
		mul=1;
		delta=0;
	}
};
struct info{
	Int mi,ma,sz,sm;
	info(){
	}
	info(Int val):mi(val),ma(val),sz(1),sm(val){
	}
	info(Int _mi,Int _ma,Int _sz,Int _sm):mi(_mi),ma(_ma),sz(_sz),sm(_sm){
	}
	friend info operator + (const info &a,const info &b){
		return info(min(a.mi,b.mi),max(a.ma,b.ma),a.sz+b.sz,a.sm+b.sm);
	}
	void operator += (const flag &f){
		if(mi==inf) return;
		mi=mi*f.mul+f.delta;
		ma=ma*f.mul+f.delta;
		sm=sm*f.mul+sz*f.delta;
	}
};

struct node *null;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
void Insert(node *u,node *x);
struct node{
	edge *son;
	void dfs(){
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->dfs();
			Insert(this,e->ed);
		}
		update();
		Update();
	}
	
	info val;
	void init(){
		l=r=pa=null;
		lis=null;
		L=R=Pa=null;
	}
	
	node *l,*r,*pa;
	bool rev;
	info cha,sub,all;
	flag chaf,subf;
	flag lisf;
	node *lis;
	bool istop(){
		return pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
		if(this==null) return;
		cha=l->cha+val+r->cha;
		lis->addragf(lisf);
		lisf.clear();
		sub=l->sub+lis->rag+r->sub;
		all=cha+sub;
	}
	void reverse(){
		if(this==null) return;
		rev^=1;
		swap(l,r);
	}
	void addchaf(flag &f){
		if(this==null) return;
		chaf+=f;
		cha+=f;
		val+=f;
		all=cha+sub;
	}
	void addsubf(flag &f){
		if(this==null) return;
		subf+=f;
		sub+=f;
		lisf+=f;
		all=cha+sub;
	}
	void addallf(flag &f){
		if(this==null) return;
		addchaf(f);
		addsubf(f);
	}
	void down(){
		if(this==null) return;
		if(rev){
			l->reverse();
			r->reverse();
			rev=false;
		}
		l->addchaf(chaf);
		r->addchaf(chaf);
		chaf.clear();
		l->addsubf(subf);
		r->addsubf(subf);
		subf.clear();
		lis->addragf(lisf);
		lisf.clear();
	}
	node* correct(){
		node *ret;
		if(istop()) ret=this; else ret=pa->correct();
		down();
		return ret;
	}
	friend void zig(node *x){
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
	friend void zag(node *x){
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
	friend void splay(node *x){
		node *top=x->correct();
		while(!x->istop()){
			node *y=x->pa;
			if(y->istop())
				if(x==y->l) zig(x); else zag(x);
			else
				if(y==y->pa->l)
					if(x==y->l)
						zig(y),zig(x);
					else
						zag(x),zig(x);
				else
					if(x==y->r)
						zag(y),zag(x);
					else
						zig(x),zag(x);
		}
		x->update();
		if(top==top->Pa->L)
			top->Pa->L=x;
		else
		if(top==top->Pa->R)
			top->Pa->R=x;
		else
			top->Pa->lis=x;
		x->Pa=top->Pa;
		x->L=top->L; if(x->L!=null) x->L->Pa=x;
		x->R=top->R; if(x->R!=null) x->R->Pa=x;
		x->rag=top->rag;
		x->ragf=top->ragf;
	}
	
	node *L,*R,*Pa;
	info rag;
	flag ragf;
	bool Istop(){
		return Pa==null||Pa->L!=this&&Pa->R!=this;
	}
	void Update(){
		if(this==null) return;
		rag=L->rag+all+R->rag;
	}
	void addragf(flag &f){
		if(this==null) return;
		ragf+=f;
		rag+=f;
		addallf(f);
	}
	void Down(){
		if(this==null) return;
		L->addragf(ragf);
		R->addragf(ragf);
		ragf.clear();
	}
	node* Correct(){
		node *ret;
		if(Istop()) ret=this; else ret=Pa->Correct();
		Down();
		return ret;
	}
	friend void Zig(node *x){
		node *y=x->Pa,*z=y->Pa;
		if(y==z->L) z->L=x; else
		if(y==z->R) z->R=x;
		x->Pa=z;
		y->L=x->R;
		x->R->Pa=y;
		x->R=y;
		y->Pa=x;
		y->Update();
	}
	friend void Zag(node *x){
		node *y=x->Pa,*z=y->Pa;
		if(y==z->L) z->L=x; else
		if(y==z->R) z->R=x;
		x->Pa=z;
		y->R=x->L;
		x->L->Pa=y;
		x->L=y;
		y->Pa=x;
		y->Update();
	}
	friend void Splay(node *x){
		x->Correct();
		while(!x->Istop()){
			node *y=x->Pa;
			if(y->Istop())
				if(x==y->L) Zig(x); else Zag(x);
			else
				if(y==y->Pa->L)
					if(x==y->L)
						Zig(y),Zig(x);
					else
						Zag(x),Zig(x);
				else
					if(x==y->R)
						Zag(y),Zag(x);
					else
						Zig(x),Zag(x);
		}
		x->Update();
		x->Pa->lis=x;
	}
} V[N];

node* merge(node *u,node *v){
	if(v==null) return u;
	for(;v->L!=null;v=v->L);
	Splay(v);
	v->L=u;
	if(u!=null) u->Pa=v;
	v->Update();
	return v;
}
void Insert(node *u,node *x){
	u->down();
	x->L=u->lis;
	x->L->Pa=x;
	x->R=null;
	u->lis=x;
	x->Pa=u;
	x->Update();
}
void Del(node *x){
	Splay(x);
	x->Pa->down();
	x->Down();
	x->L->Pa=null;
	x->R->Pa=null;
	x->Pa->lis=merge(x->L,x->R);
	if(x->Pa->lis!=null) x->Pa->lis->Pa=x->Pa;
	x->Pa=null;
	x->L=null;
	x->R=null;
}

node* access(node *x){
	node *y=null;
	while(x!=null){
		splay(x);
		if(x->r!=null){
			node *t=x->r;
			x->r=null;
			t->ragf.clear();
			t->Update();
			Insert(x,t);
		}
		if(y!=null){
			Del(y);
			x->r=y;
		}
		x->update();
		y=x;
		x=x->pa;
	}
	return y;
}

void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++;
	*newE=(edge){u,v->son},v->son=newE++;
}

node *root;

void makeroot(node *x){
	access(x);
	splay(x);
	x->reverse();
	root=x;
}

int main(){
	null=V;
	null->init();
	null->cha.mi=inf;
	null->sub.mi=inf;
	null->all.mi=inf;
	null->rag.mi=inf;
	n=getint();
	int m=getint();
	for(int i=1;i<n;i++)
		addedge(V+getint(),V+getint());
	for(node *u=V+1;u<=V+n;u++){
		u->init();
		u->val=getint();
	}
	root=V+getint();
	root->dfs();
	while(m--){
		int type=getint();
		if(type==0){
			node *x=V+getint();
			flag f(0,getint());
			access(x);
			splay(x);
			x->val+=f;
			x->lisf+=f;
			x->update();
		}
		else
		if(type==1){
			makeroot(V+getint());
		}
		else
		if(type==2){
			node *r=root,*x=V+getint(),*y=V+getint();
			makeroot(x);
			access(y);
			splay(y);
			flag f(0,getint());
			y->addchaf(f);
			makeroot(r);
		}
		else
		if(type==3||type==4||type==11){
			node *x=V+getint();
			access(x);
			splay(x);
			info ans=x->val+x->lis->rag;
			Int res;
			printf("%d\n",res=type==3?ans.mi:type==4?ans.ma:ans.sm);
		}
		else
		if(type==5){
			node *x=V+getint();
			access(x);
			splay(x);
			flag f(1,getint());
			x->val+=f;
			x->lisf+=f;
			x->update();
		}
		else
		if(type==6){
			node *r=root,*x=V+getint(),*y=V+getint();
			makeroot(x);
			access(y);
			splay(y);
			flag f(1,getint());
			y->addchaf(f);
			makeroot(r);
		}
		else
		if(type==7||type==8||type==10){
			node *r=root,*x=V+getint(),*y=V+getint();
			makeroot(x);
			access(y);
			splay(y);
			info ans=y->cha;
			Int res;
			printf("%d\n",res=type==7?ans.mi:type==8?ans.ma:ans.sm);
			makeroot(r);
		}
		else
		if(type==9){
			node *x=V+getint(),*y=V+getint();
			access(x);
			if(access(y)==x) continue;
			access(x);
			splay(x);
			if(x->l!=null){
				x->l->pa=null;
				x->l=null;
				x->update();
			}
			access(y);
			splay(y);
			x->pa=y;
			Insert(y,x);
			y->update();
		}
	}
}

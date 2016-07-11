#include <cstdio>
#include <algorithm>
using namespace std;
const unsigned N=100001,Q=100000,P=51061;
unsigned n,m,q;

unsigned getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
void print(unsigned a){
	if(a>9) print(a/10); putchar('0'+a%10);
}

struct node *null;
struct node{
	node *l,*r,*pa; bool rev; unsigned w,size,add,mul,sum;
	void clear(){
		l=r=pa=null;
		rev=false;
		sum=w=1;
		size=1;
		add=0;
		mul=1;
	}
	bool istop(){
		return this==null||pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
		size=(l->size+r->size+1)%P;
		sum=(l->sum+r->sum+w)%P;
	}
	void reverse(){
		rev^=1;
		swap(l,r);
	}
	void plus(const unsigned delta){
		add=(add+delta)%P;
		w=(w+delta)%P;
		sum=(sum+size*delta)%P;
	}
	void mult(const unsigned delta){
		mul=mul*delta%P;
		add=add*delta%P;
		w=w*delta%P;
		sum=sum*delta%P;
	}
	void down(){
		if(rev){
			l->reverse();
			r->reverse();
			rev=false;
		}
		if(mul!=1){
			l->mult(mul);
			r->mult(mul);
			mul=1;
		}
		if(add){
			l->plus(add);
			r->plus(add);
			add=0;
		}
	}
	void correct(){
		if(!istop()) pa->correct();
		down();
	}
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

int main(){
	null=V;
	n=getint(); q=getint();
	for(int i=0;i<=n;i++) V[i].clear();
	null->size=0;
	null->sum=null->w=0;
	for(int i=1;i<n;i++)
		link(V+getint(),V+getint());
	node *u,*v,*lca; unsigned c;
	while(q--)
		switch(getchar()){
			case '+': u=V+getint(); v=V+getint(); c=getint();
				access(u);
				lca=access(v);
				lca->w=(lca->w+c)%P;
				lca->r->plus(c);
				lca->update();
				access(u);
				lca->r->plus(c);
				break;
			case '-':
				cut(V+getint(),V+getint());
				link(V+getint(),V+getint());
				break;
			case '*': u=V+getint(); v=V+getint(); c=getint();
				access(u);
				lca=access(v);
				lca->w=lca->w*c%P;
				lca->r->mult(c);
				lca->update();
				access(u);
				lca->r->mult(c);
				break;
			case '/': u=V+getint(); v=V+getint();
				access(u);
				lca=access(v);
				c=lca->w+lca->r->sum;
				access(u);
				c+=lca->r->sum;
				print(c%P),putchar('\n');
				break;
			default: q++;
		}
}

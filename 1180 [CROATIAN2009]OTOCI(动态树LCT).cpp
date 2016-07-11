#include <cstdio>
#include <algorithm>
using namespace std;
const int N=30005;
int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
int n;
struct node *null;
struct node{
	node *l,*r,*pa;
	bool rev;
	int a,s;
	void init(){
		l=r=pa=null;
		a=s=0;
	}
	bool istop(){
		return pa==null||pa->l!=this&&pa->r!=this;
	}
	void reverse(){
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
	void update(){
		s=l->s+r->s+a;
	}
	void correct(){
		if(!istop()) pa->correct(); down();
	}
} V[N];
int num(node *u){
	return u-V;
}
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
	}
	x->update();
}
node* access(node *x){
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
void makeroot(node *u){
	access(u);
	splay(u);
	u->reverse();
}
bool link(node *u,node *v){
	if(u==v) return false;
	makeroot(u);
	makeroot(v);
	if(u->pa!=null) return false;
	v->pa=u;
	return true;
}
int query(node *u,node *v){
	if(u==v) return u->a;
	makeroot(u);
	access(v);
	splay(v);
	if(u->pa==null) return -1;
	return v->s;
}
int main(){
	null=V;
	null->init();
	n=getint();
	for(int i=1;i<=n;i++) V[i].init(),scanf("%d",&V[i].a),V[i].s=V[i].a;
	int q=getint();
	while(q--){
		static char opt[20];
		scanf("%s",opt);
		if(opt[0]=='b')
			puts(link(V+getint(),V+getint())?"yes":"no");
		else
		if(opt[0]=='p'){
			int x=getint();
			splay(V+x);
			V[x].a=getint();
			V[x].update();
		}
		else{
			int ans=query(V+getint(),V+getint());
			if(ans==-1)
				puts("impossible");
			else
				printf("%d\n",ans);
		}
	}
}

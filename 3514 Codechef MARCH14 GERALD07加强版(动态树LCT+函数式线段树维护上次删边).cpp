#include <cstdio>
#include <algorithm>
using namespace std;

const int N=200005,logN=19;

int n,m,k,type,x[N],y[N],seq[N];

int X;

struct tree{
	tree *l,*r;
	int cnt;
} *root[N],mem[N*logN],*newtree=mem;

tree* insert(tree *last,int beg,int end){
	tree *cur=newtree++;
	if(last) *cur=*last;
	cur->cnt++;
	if(end-beg==1) return cur;
	int mid=beg+end>>1;
	if(X<mid)
		cur->l=insert(cur->l,beg,mid);
	else
		cur->r=insert(cur->r,mid,end);
	return cur;
}

int query(tree *cur,int beg,int end){
	if(!cur||end<=0||beg>=X) return 0;
	if(0<=beg&&end<=X) return cur->cnt;
	int mid=beg+end>>1;
	return query(cur->l,beg,mid)+query(cur->r,mid,end);
}

struct node *null;
struct node{
	node *l,*r,*pa;
	int a;
	bool rev;
	node *mi;
	void init(){
		l=r=pa=null;
		mi=this;
		a=N;
	}
	bool istop(){
		return pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
		mi=this;
		if(l->mi->a<mi->a) mi=l->mi;
		if(r->mi->a<mi->a) mi=r->mi;
	}
	void reverse(){
		if(this==null) return;
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
	void correct(){
		if(!istop()) pa->correct(); down();
	}
} V[N],E[N];

void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	x->r->pa=y;
	y->l=x->r;
	x->r=y;
	y->pa=x;
	y->update();
}
void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	x->l->pa=y;
	y->r=x->l;
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

void link(node *x,node *y){
	access(x);
	splay(x);
	x->reverse();
	x->pa=y;
}

void cut(node *x,node *y){
	access(y);
	splay(x);
	if(x->pa==y){
		x->pa=null;
		return;
	}
	access(x);
	splay(y);
	if(y->pa==x){
		y->pa=null;
		return;
	}
	puts("Error while cutting");
}

int main(){
	null=V;
	null->init();
	scanf("%d%d%d%d",&n,&m,&k,&type);
	for(int i=1;i<=m;i++){
		scanf("%d%d",x+i,y+i);
		E[i].init();
		E[i].a=i;
	}
	for(int i=1;i<=n;i++){
		V[i].init();
		V[i].a=N;
	}
	for(int i=1;i<=m;i++){
		node *u=V+x[i],*v=V+y[i];
		if(u==v){
			seq[i]=-1;
			continue;
		}
		access(u);
		splay(u);
		u->reverse();
		access(v);
		splay(v);
		if(u->pa!=null){
			node *w=v->mi;
			int e=w-E;
			seq[i]=e;
			cut(E+e,V+x[e]);
			cut(E+e,V+y[e]);
		}
		else
			seq[i]=0;
		link(E+i,V+x[i]);
		link(E+i,V+y[i]);
	}
	for(int i=1;i<=m;i++)
		if(seq[i]==-1)
			root[i]=root[i-1];
		else{
			X=seq[i];
			root[i]=insert(root[i-1],0,m+1);
		}
	int ans=0;
	while(k--){
		int l,r; scanf("%d%d",&l,&r);
		if(type) l^=ans,r^=ans;
		X=l;
		l--;
		ans=n-query(root[r],0,m+1)+query(root[l],0,m+1);
		printf("%d\n",ans);
	}
}

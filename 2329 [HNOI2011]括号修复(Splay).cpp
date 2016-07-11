/*
对于询问的一段区间，把匹配的删去后剩下的一定是)))(((的形式。
把(当+1,)当-1， 
左边)的个数即为左边起的最小前缀和 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=100005;

int gc(){
	char c;
	while(c=getchar(),c!='('&&c!=')');
	return c=='('?1:-1;
}

int n;
struct node *null;
struct node{
	node *pa,*l,*r;
	int a;
	int size,sum,lmin,lmax,rmin,rmax;
	int cov,rev,inv; //rev: 0 1  cov: -1 0 1  inv: 0 1
	int query(){
		return (-lmin+1)/2+(rmax+1)/2;
	}
	void update(){
		if(this==null) return;
		size=l->size+r->size+1;
		sum=l->sum+r->sum+a;
		lmin=min(l->lmin,l->sum+a+r->lmin);
		lmax=max(l->lmax,l->sum+a+r->lmax);
		rmin=min(r->rmin,r->sum+a+l->rmin);
		rmax=max(r->rmax,r->sum+a+l->rmax);
	}
	void cover(int c){
		if(this==null) return;
		cov=c;
		rev=0;
		inv=0;
		a=c;
		sum=size*c;
		lmin=min(0,sum);
		lmax=max(0,sum);
		rmin=min(0,sum);
		rmax=max(0,sum);
	}
	void reverse(){
		if(this==null) return;
		if(cov) return;
		rev^=1;
		swap(l,r);
		swap(lmin,rmin);
		swap(lmax,rmax);
	}
	void invert(){
		if(this==null) return;
		if(cov)
			cov*=-1;
		else
			inv^=1;
		a*=-1;
		sum*=-1;
		swap(lmin,lmax);
		lmin*=-1;
		lmax*=-1;
		swap(rmin,rmax);
		rmin*=-1;
		rmax*=-1;
	}
	void down(){
		if(this==null) return;
		if(cov){
			l->cover(cov);
			r->cover(cov);
			cov=0;
		}
		if(rev){
			l->reverse();
			r->reverse();
			rev=0;
		}
		if(inv){
			l->invert();
			r->invert();
			inv=0;
		}
	}
	void correct(){
		if(this==null) return; pa->correct(); down();
	}
	node *getkth(int k){
		down();
		if(k<l->size+1)
			return l->getkth(k);
		if(k>l->size+1)
			return r->getkth(k-(l->size+1));
		return this;
	}
};
void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(z!=null){
		if(z->l==y) z->l=x; else
		if(z->r==y) z->r=x;
	}
	x->pa=z;
	y->l=x->r;
	x->r->pa=y;
	x->r=y;
	y->pa=x;
	y->update();
}
void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(z!=null){
		if(z->l==y) z->l=x; else
		if(z->r==y) z->r=x;
	}
	x->pa=z;
	y->r=x->l;
	x->l->pa=y;
	x->l=y;
	y->pa=x;
	y->update();
}
void splay(node *x,node *&goal){
	node *top=goal->pa;
	x->correct();
	while(x->pa!=top){
		node *y=x->pa,*z=y->pa;
		if(z==top)
			if(x==y->l) zig(x); else zag(x);
		else
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
	goal=x;
	x->update();
}


node nuller,V[N];
node *root;
node *build(int beg,int end,node *pa){
	if(beg==end) return null;
	int mid=beg+end>>1;
	V[mid].pa=pa;
	V[mid].l=build(beg,mid,V+mid);
	if(mid>=1&&mid<=n)
		V[mid].a=gc();
	V[mid].r=build(mid+1,end,V+mid);
	V[mid].update();
	return V+mid;
}


int main(){
	freopen("brackets.in","r",stdin);
	freopen("brackets.out","w",stdout);
	null=&nuller;
	null->pa=null->l=null->r=null;
	int m; scanf("%d%d",&n,&m);
	root=build(0,n+2,null);
	while(m--){
		static char type[10];
		int l,r;
		scanf("%s%d%d",type,&l,&r);
		r+=2;
		splay(root->getkth(l),root);
		splay(root->getkth(r),root->r);
		root->update();
		node *cur=root->r->l;
		cur->correct();
		if(type[0]=='R'){
			cur->cover(gc());
		}
		else
		if(type[0]=='S'){
			cur->reverse();
		}
		else
		if(type[0]=='I'){
			cur->invert();
		}
		else
		if(type[0]=='Q'){
			printf("%d\n",cur->query());
		}
		else
			puts("Error: Cannot identify this type!");
		root->r->update();
		root->update();
	}
	scanf("\n");
}

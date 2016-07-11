#include <cstdio>
#include <algorithm>
using std::swap;
template<class T>
T ave(const T &a,const T &b){
	return a+((b-a)>>1);
}
struct Splay *null,*root;
inline void nullinit();
struct Splay{
	Splay *l,*r,*pa;
	bool rev; int size;
	Splay():pa(null),l(null),r(null),rev(false),size(1){
	}
	Splay(Splay* st,Splay* en,Splay* Pa):
		pa(Pa),rev(false),size(en-st){
		l=st<this?new(ave(st,this)) Splay(st,this,this):null;
		r=this+1<en?new(ave(this+1,en)) Splay(this+1,en,this):null;
	}
	inline void down(){
		if(rev) swap(l,r),l->rev^=1,r->rev^=1,rev=false;
	}
	inline void update(){
		size=l->size+r->size+1;
	}
	#define x this
	void zig(){
		Splay *y=x->pa,*z=y->pa;
		x->pa=z; (y==z->l?z->l:z->r)=x;
		x->r->pa=y; y->l=x->r;
		x->r=y; y->pa=x;
		y->update();
	}
	void zag(){
		Splay *y=x->pa,*z=y->pa;
		x->pa=z; (y==z->l?z->l:z->r)=x;
		x->l->pa=y; y->r=x->l;
		x->l=y; y->pa=x;
		y->update();
	}
	void currect(){ if(pa!=null) pa->currect(),pa->down(); }
	void splay(){ splay(root); }
	void splay(Splay* &goal){
		if(this==null) return;
		currect();
		down();
		Splay *y,*z,*top=goal->pa;
		while((y=pa)!=top)
			if((z=y->pa)==top) x==y->l?zig():zag(); else
			if(y==z->l)
				if(x==y->l) y->zig(),zig(); else zag(),zig();
			else
				if(x==y->r) y->zag(),zag(); else zig(),zag();
		update();
		goal=this;
	}
	#undef x
	Splay* nth(int k){
		Splay *x=this;
		int mid;
		while(x!=null){
			x->down();
			mid=x->l->size+1;
			if(k<mid) x=x->l; else
			if(mid<k) x=x->r,k-=mid; else
			return x;
		}
		return null;
	}
	void PrintinLine();
	void PrintLine();
} ele[100005];
Splay* build(Splay* st,Splay* en){
	return new(ave(st,en)) Splay(st,en,null);
}
int n,m,l,r,leftprint;
void Splay::PrintinLine(){
	leftprint=size;
	PrintLine();
}
void Splay::PrintLine(){
	if(this==null) return;
	down();
	l->PrintLine();
	printf("%u",this-ele); if(--leftprint) putchar(' ');
	r->PrintLine();
}
Splay* select(const int begin,const int end){
	root->nth(begin-1)->splay(root);
	root->nth(end+1)->splay(root->r);
	return root->r->l;
}
void nullinit(){ null->size=0; null->l=null->r=null->pa=null; }
int main(){
	scanf("%u%u",&n,&m);
	null=new Splay;
	nullinit();
	root=build(ele,ele+n+2);
	while(m--){
		scanf("%u%u",&l,&r);
		select(l+1,r+1)->rev^=1;
	}
	select(2,n+1)->PrintinLine();
}

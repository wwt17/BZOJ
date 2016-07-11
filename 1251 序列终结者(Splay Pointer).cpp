#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define inf 0x7fffffff
#define root Seq
inline bool mini(int &a,const int b) { return a>b?(a=b,true):false; }
struct Splay *null,*base,*root;
void nullinit();
struct Splay {
	Splay *l,*r,*fa;
	int data,size;
	int add;bool rev;int max;
	Splay():l(null),r(null),fa(null),data(0),size(1),add(0),rev(0),max(0) {}
	Splay(int Data,Splay* Fa):l(null),r(null),fa(Fa),data(Data),size(1),add(0),rev(0),max(0) {}
	void clear() { Splay(); }
	inline Splay* updata() {
		size=l->size+r->size+1;
		max=std::max(l->max,r->max);
	}
	inline Splay* downdata() {
		
	void zig() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->r->fa=y; y->l=x->r;
		x->r=y; y->fa=x;
		y->updata();
		x->updata();
	}
	void zag() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->l->fa=y; y->r=x->l;
		x->l=y; y->fa=x;
		y->updata();
		x->updata();
	}
	Splay* splay() { nullinit(); splay(root); }
	Splay* splayc() { nullinit(); splayc(this); }
	Splay* splayc(Splay* Root) { Splay* tmp=Root; return splay(tmp); }
	Splay* splay(Splay* &Root) {
		Splay *y,*z,*rf=Root->fa;
		while (fa!=rf) {
			y=fa; z=y->fa;
			if (z==null) this==y->l?zig():zag(); else
			if (y==z->l) this==y->l?(y->zig(),zig()):(zag(),zig());
			        else this==y->r?(y->zag(),zag()):(zig(),zag());
		}
		updata();
		return Root=this;
	}
	Splay* cutl() {
		Splay *x=this,*y;
		while (x->l!=null) x=x->l;
		x->r->fa=x->fa; (x==x->fa->l?x->fa->l:x->fa->r)=x->r;
		for (y=x->fa;y!=null;y=y->fa) --y->size;
		x->r=x->fa=null;
		return x;
	}
	Splay* cutr() {
		Splay *x=this,*y;
		while (x->r!=null) x=x->r;
		x->l->fa=x->fa; (x==x->fa->l?x->fa->l:x->fa->r)=x->l;
		for (y=x->fa;y!=null;y=y->fa) --y->size;
		x->l=x->fa=null;
		return x->splayc();
	}
	Splay* getl() {
		Splay *x=this;
		while (x->l!=null) x=x->l;
		return x->splayc();
	}
	Splay* getr() {
		Splay *x=this;
		while (x->r!=null) x=x->r;
		return x->splayc();
	}
	Splay* ins(int Data) {
		Splay *x=this,*y=fa;
		while (x!=null) {
			++x->size;
			y=x;
			x=(Data<=x->data?x->l:x->r);
		}
		x=(Data<=y->data?y->l:y->r)=new Splay(Data,y);
		return x->splay();
	}
	Splay* ins(Splay* node,int k) {
		if (k>size) {
			node->l=this;
			this->fa=node;
			node->size=size+1;
			return node;
		}
		Splay *x=No(k);
		node->r=x; x->fa=node;
		node->l=x->l;
		x->size-=x->l->size;
		x->l=null;
		node->l->fa=node;
		node->fa=null;
		node->updata();
		return node;
	}
	Splay* Cut() {
		(this==fa->l?fa->l:fa->r)=null;
		fa->splay();
		fa=null;
		return this;
	}
	Splay* cut() {
		splay();
		Splay *x=(l!=null?l->cutr():r!=null?r->cutl():null);
		x->l=l; x->l->fa=x;
		x->r=r; x->r->fa=x;
		x->updata();
		l=r=fa=null;
		size=0;
		return x;
	}
	void Del() {
		if (this==null) return;
		l->Del();
		r->Del();
		(this==fa->l?fa->l:fa->r)=null;
		delete this;
	}
	Splay* del() {
		splay();
		Splay *x=(l!=null?l->cutr():r!=null?r->cutl():null);
		x->l=l; x->l->fa=x;
		x->r=r; x->r->fa=x;
		x->updata();
		delete this;
		return x;
	}
	Splay* No(int k) {
		if (size<k) return null;
		Splay* x=this;
		int mid;
		while (x!=null) {
			x->downdata();
			mid=x->l->size+1;
			if (k<mid) x=x->l; else
			if (k>mid) x=x->r,k-=mid; else
			return x->splay();
		}
	}
	int No() {
		if (this==null) return 0;
		splay();
		return l->size+1;
	}
	Splay* lower_bound(int Data) {
		Splay *x=this,*ret=null;
		while (x!=null) x=(Data<=x->data?(ret=x,x->l):x->r);
		return ret->splay();
	}
	Splay* closest(int Data) {
		Splay *x=this,*ret;
		int dist=inf,_dist;
		while (x!=null) {
			if (_dist=x->data-Data,abs(_dist)<dist||_dist==-dist)
				ret=x,dist=abs(_dist);
			x=(Data<=x->data?x->l:x->r);
		}
		return ret;
	}
	Splay* Cut(int L,int R,Splay* &left,Splay* &right) {
		Splay* x=No(L);
		left=x->l->Cut();
		x=No(R);
		right=x->r->Cut();
		return x;
	}
	bool isl() { return fa->l==this; }
	Splay* lcnct(Splay* x) { l=x; x->fa=this; return this; }
	Splay* rcnct(Splay* x) { r=x; x->fa=this; return this; }
	Splay* cnctl(Splay* y) { y->l=this; fa=y; return this; }
	Splay* cnctr(Splay* y) { y->r=this; fa=y; return this; }
	Splay* pctgr(Splay* left,Splay* right) {
		return
			left!=null?left->getr()->rcnct(right)->updata():
			right!=null?right->getl()->lcnct(left)->updata():
			null;
	}
	Splay* pctgr(Splay* left,Splay* mid,Splay* right) {
		return pctgr(left,pctgr(mid,right));
	}
	Splay* plus(int L,int R,int V) {
		Splay *left,*right,*mid=Cut(L,R,left,right);
		mid->add+=V;
		return pctgr(left,mid,right);
	}
	Splay* reverse(int L,int R) {
		Splay *left,*right,*mid=Cut(L,R,left,right);
		mid->rev^=1;
		return pctgr(left,mid,right);
	}
	Splay* maxsum(int L,int R) {
		Splay *
	void print() {
		printf("%d l=%d r=%d fa=%d size=%d\n",
		this-base,l-base,r-base,fa-base,size);
	}
	void print(char name[]) { printf("%s ",name); print(); }
	void printtree(int tab) {
		if (this==null) return;
		int i;
		for (i=1;i<=tab;++i) printf("  "); if (i==tab+1) print();
		l->printtree(tab+1);
		r->printtree(tab+1);
		//for (i=1;i<=tab;++i) printf("  "); if (i==tab+1) printf("END\n");
	}
	void printtree() { printf("\n"); printtree(0); }
	void printline() {
		if (this==null) return;
		l->printline();
		printf(" %d",this-base);
		r->printline();
	}
};
void nullinit() { null->l=null->r=null->fa=null; null->size=0; }
Splay* build(Splay* l,Splay* r,Splay* Fa) {
	if (l>r) return null;
	Splay *mid=l+(r-l)/2;
	mid->l=build(l,mid-1,mid);
	mid->r=build(mid+1,r,mid);
	mid->fa=Fa;
	mid->size=mid->l->size+mid->r->size+1;
	return mid;
}
int main() {
	int N,M,K,L,R,V;
	scanf("%d%d",&N,&M);
	null=new Splay;nullinit();
	Splay seq[N+1],*Seq=build(seq+1,seq+N,null);
	while (M--) {
		scanf("%d%d%d",&K,&L,&R);
		switch (K) {
			case 1: scanf("%d",&V); Seq->plus(L,R,V); break;
			case 2: Seq->reverse(L,R); break;
			case 3: Seq->maxsum(L,R); break;
		}
	}
	for(;;);
}

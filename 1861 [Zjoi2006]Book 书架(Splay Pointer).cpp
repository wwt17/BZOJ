#include <cstdio>
#include <cstdlib>
#define inf 0x7fffffff
inline bool mini(int &a,const int b) { return a>b?(a=b,true):false; }
struct Splay *null,*base,*shelf=null;
void Splayinit();
struct Splay {
	Splay *l,*r,*fa;
	int size;
	Splay():l(null),r(null),fa(null),size(0) {}
	Splay(int Data,Splay* Fa):l(null),r(null),fa(Fa),size(1) {}
	void clear() { Splay(); }
	void update() { size=l->size+r->size+1; }
	void zig() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->r->fa=y; y->l=x->r;
		x->r=y; y->fa=x;
		y->update();
	}
	void zag() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->l->fa=y; y->r=x->l;
		x->l=y; y->fa=x;
		y->update();
	}
	Splay* splay() {
		if (this==null) return this;
		Splay *y,*z;
		while (fa!=null) {
			y=fa; z=y->fa;
			if (z==null) this==y->l?zig():zag(); else
			if (y==z->l) this==y->l?(y->zig(),zig()):(zag(),zig());
			        else this==y->r?(y->zag(),zag()):(zig(),zag());
		}
		update();
		return this;
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
		return x;
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
		node->update();
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
		x->update();
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
	Splay* No(int k) {
		if (size<k) return null;
		Splay* x=this;
		int mid;
		while (x!=null) {
			mid=x->l->size+1;
			if (k<mid) x=x->l; else
			if (k>mid) x=x->r,k-=mid; else
			return x->splay();
		}
	}
	int No() {
		if (this==null) return 0;
		shelf=splay();
		return l->size+1;
	}
	Splay* build(Splay** l,Splay** r,Splay* Fa) {
		if (l>r) return null;
		Splay **mid=l+(r-l)/2,*ret=*mid;
		ret->l=build(l,mid-1,ret);
		ret->r=build(mid+1,r,ret);
		ret->fa=Fa;
		ret->size=ret->l->size+ret->r->size+1;
		return ret;
	}
};
void Splayinit() { null->l=null->r=null->fa=null; null->size=0; }
int main() {
	freopen("book.in","r",stdin);
	freopen("book.out","w",stdout);
	int n,m,S,X,p;
	scanf("%d%d",&n,&m);
	null=new Splay; Splayinit();
	Splay book[n+1]; base=book;
	for (int i=1;i<=n;++i) book[i].size=1;
	Splay* s[n+1];
	for (int i=1;i<=n;++i) scanf("%d",&S),s[i]=book+S; scanf("\n");
	shelf=shelf->build(s+1,s+n,null);
	char opt[8];
	while (m--) {
		Splayinit();
		scanf("%s%d",opt,&S);
		switch (*opt) {
			case 'T':
				shelf=book[S].cut()->ins(book+S,1);
				break;
			case 'B':
				shelf=book[S].cut()->ins(book+S,n+1);
				break;
			case 'I':
				scanf("%d",&X);
				if (!X) break;
				p=book[S].No();
				shelf=book[S].cut();
				shelf=shelf->ins(book+S,p+X);
				break;
			case 'A':
				printf("%d\n",book[S].No()-1);
				break;
			case 'Q':
				printf("%d\n",(shelf=shelf->No(S))-book);
		}
	}
}

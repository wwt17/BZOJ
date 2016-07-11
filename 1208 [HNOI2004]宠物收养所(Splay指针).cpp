#include <cstdio>
#include <cstdlib>
#define inf 0x7fffffff
#define bound inf
inline bool mini(int &a,const int b)
	{ if (a>b) { a=b; return true; } return false; }
int ans,dist,count;
struct Splay *null;
struct Splay {
	Splay *l,*r,*fa;
	int data;
	Splay():l(null),r(null),fa(null),data(0) {}
	Splay(int Data,Splay* Fa):l(null),r(null),fa(Fa),data(Data) {}
	void clear() { Splay(); }
	void update() {}
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
		Splay *y,*z;
		if (this==null) return this;
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
		Splay* x=this;
		while (x->l!=null) x=x->l;
		x->r->fa=x->fa; (x==x->fa->l?x->fa->l:x->fa->r)=x->r;
		x->r=x->fa=null;
		return x;
	}
	Splay* cutr() {
		Splay* x=this;
		int cnt=bound;
		while (x->r!=null) x=x->r;
		x->l->fa=x->fa; (x==x->fa->l?x->fa->l:x->fa->r)=x->l;
		x->l=x->fa=null;
		return x;
	}
	Splay* del() {
		splay();
		Splay *x=(l!=null?l->cutr():r!=null?r->cutl():null);
		x->l=l; x->l->fa=x;
		x->r=r; x->r->fa=x;
		delete this;
		return x;
	}
	Splay* ins(int Data) {
		Splay *x=this,*y=fa;
		while (x!=null) {
			y=x;
			x=(Data<=x->data?x->l:x->r);
		}
		x=(Data<=y->data?y->l:y->r)=new Splay(Data,y);
		return 1?x->splay():this;
	}
	Splay* closest(int Data) {
		Splay *x=this,*ret;
		dist=inf; int _dist;
		while (x!=null) {
			if (_dist=x->data-Data,abs(_dist)<dist||_dist==-dist)
				ret=x,dist=abs(_dist);
			x=(Data<=x->data?x->l:x->r);
		}
		return ret;
	}
	void print() {
		printf("root=%d left=%d right=%d father=%d\n",data,l->data,r->data,fa->data);
	}
	void print(char name[]) { printf("%s ",name); print(); }
	void printtree(int tab) {
		if (this==null) return;
		int i;
		for (i=1;i<=tab;++i) printf(" "); if (i==tab+1) print();
		l->printtree(tab+1);
		r->printtree(tab+1);
		for (i=1;i<=tab;++i) printf(" ");	if (i==tab+1) printf("END\n");
	}
	void printtree() {
		printtree(0);
	}
};
void Splayinit() { null=new Splay; null->l=null->r=null->fa=null; }
int main() {
	freopen("pet.in","r",stdin);
	freopen("pet.out","w",stdout);
	#define P 1000000
	int n,a,b;
	scanf("%d",&n);
	Splayinit();
	Splay *pe=null,*c;
	while (n--) {
		scanf("%d%d",&a,&b);
		if (a)
			if (count++<0) {
				pe=pe->closest(b)->del();
				ans=(ans+dist)%P;
			} else pe=pe->ins(b);
		else
			if (count-->0) {
				pe=pe->closest(b)->del();
				ans=(ans+dist)%P;
			} else pe=pe->ins(b);
	}
	printf("%d\n",ans);
}

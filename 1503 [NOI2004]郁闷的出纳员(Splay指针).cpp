#include <cstdio>
#include <cstdlib>
#define inf 0x7fffffff
inline bool mini(int &a,const int b) { return a>b?(a=b,true):false; }
struct Splay *null;
int base;
struct Splay {
	Splay *l,*r,*fa;
	int data,size;
	Splay():l(null),r(null),fa(null),data(0),size(0) {}
	Splay(int Data,Splay* Fa):l(null),r(null),fa(Fa),data(Data),size(1) {}
	void clear() { Splay(); }
	void update() { size=l->size+r->size+1; }
	void zig() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->r->fa=y; y->l=x->r;
		x->r=y; y->fa=x;
		y->update();
		x->update();
	}
	void zag() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->l->fa=y; y->r=x->l;
		x->l=y; y->fa=x;
		y->update();
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
			y->update();
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
			++x->size;
			y=x;
			x=(Data<=x->data?x->l:x->r);
		}
		x=(Data<=y->data?y->l:y->r)=new Splay(Data,y);
		return x->splay();
	}
	Splay* lower_bound(int Data) {
		Splay *x=this,*ret=null;
		while (x!=null) x=(Data<=x->data?(ret=x,x->l):x->r);
		return ret->splay();
	}
	Splay* Cut() {
		(this==fa->l?fa->l:fa->r)=null;
		fa=null;
		return this;
	}
	void Del() {
		if (this==null) return;
		l->Del();
		r->Del();
		(this==fa->l?fa->l:fa->r)=null;
		fa->update();
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
	void print() {
		printf("root=%d left=%d right=%d father=%d size=%d\n",
		data+base,l->data+base,r->data+base,fa->data+base,size);
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
	void printtree() { printtree(0); }
};
void Splayinit() { null->l=null->r=null->fa=null; null->size=0; }
int main() {
	int n,min,k,goin=0;
	scanf("%d%d",&n,&min);
	null=new Splay; Splayinit();
	Splay *com=null;
	char opt;
	while (n--) {
		scanf("\n%c%d",&opt,&k);
		switch (opt) {
			case 'I': if (k>=min) ++goin,com=com->ins(k-base); break;
			case 'A': base+=k; break;
			case 'S': base-=k; (com=com->lower_bound(min-base))->l->Del(); break;
			case 'F': printf("%d\n",k>com->size?-1:(com=com->No(com->size-k+1))->data+base);
		}
		Splayinit();
	}
	printf("%d\n",goin-com->size);
}

#include <cstdio>
#include <cstdlib>
#define inf 0x7fffffff
inline bool mini(int &a,const int b)
	{ if (a>b) { a=b; return true; } return false; }
int ans;
struct Splay *null,*sum;
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
		//printf("zig %d\n",data);
	}
	void zag() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->l->fa=y; y->r=x->l;
		x->l=y; y->fa=x;
		y->update();
		//printf("zag %d\n",data);
	}
	void splay() {
		//printf("splay: now=%d fa=%d\n",data,fa->data);
		Splay *y,*z;
		if (this==null) return;
		while (fa!=null) {
			y=fa; z=y->fa;
			if (z==null) this==y->l?zig():zag(); else
			if (y==z->l) this==y->l?(y->zig(),zig()):(zag(),zig());
			        else this==y->r?(y->zag(),zag()):(zig(),zag());
		}
		update();
		sum=this;
	}
	void insert(int Data) {
		Splay *x=this,*y=fa;
		ans=inf;
		while (x!=null) {
			mini(ans,abs(Data-x->data));
			//printf("left=%d root=%d right=%d dist=%d\n",x->l->data,x->data,x->r->data,abs(Data-x->data));
			y=x;
			x=(Data<=x->data?x->l:x->r);
		}
		((Data<=y->data?y->l:y->r)=new Splay(Data,y))->splay();
	}
};
void Splayinit() { null=new Splay; }
int main() {
	int n,now,Ans;
	scanf("%d",&n);
	scanf("%d",&Ans);
	Splayinit();
	sum=new Splay(Ans,null);
	while (--n) {
		scanf("%d",&now);
		sum->insert(now);
		//printf("left=%d root=%d right=%d\n",sum->l->data,sum->data,sum->r->data);
		//printf("ans=%d\n",ans);
		Ans+=ans;
	}
	printf("%d\n",Ans);
	system("pause");
}

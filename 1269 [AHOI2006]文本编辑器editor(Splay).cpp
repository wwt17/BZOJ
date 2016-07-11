#include <cstdio>
#include <algorithm>
using namespace std;
struct Splay *root,*null,*begin,*end;
inline void nullinit();
struct Splay{
	Splay *l,*r,*pa;
	int size; bool rev;
	char c;
	Splay():pa(null),l(null),r(null),rev(false),size(1){
	}
	Splay(char* st,char* en,Splay* Pa):
		#define mid (st+((en-st)>>1))
		pa(Pa),rev(false),size(en-st),c(*mid),
		l(st<mid?new Splay(st,mid,this):null),
		r(mid+1<en?new Splay(mid+1,en,this):null)
		#undef mid
	{}
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
	void del(){
		if(this==null) return;
		l->del();
		r->del();
		delete this;
	}
	void PrintLine();
};
void Splay::PrintLine(){
	if(this==null) return;
	down();
	l->PrintLine();
	putchar(c);
	r->PrintLine();
}
void nullinit(){ null->size=0; null->l=null->r=null->pa=null; }
char s[2*1024*1024+1];
int main(){
	null=new Splay; nullinit();
	root=begin=new Splay;
	begin->c='{';
	begin->size=0;
	begin->l=new Splay;
	begin->l->c='_';
	begin->l->size=-1;
	root->r=end=new Splay;
	end->pa=root;
	end->c='}';
	end->size=0;
	end->r=begin->l;
	int t; unsigned n;
	scanf("%u",&t);
	while(
		/*
		root->l->PrintLine(),
		putchar(root->c),putchar('|'),
		root->r->PrintLine(),
		putchar('\n'),
		*/
		t--)
		switch(scanf("\n"),getchar()){
			case 'M'://Move k
				scanf("ove %u",&n);
				root->nth(n)->splay(root);
				break;
			case 'I'://Insert n endl S
				scanf("nsert %u",&n);
				root->r->nth(1)->splay(root->r);
				for(int i=0;i<n;i++)
					while((s[i]=getchar())<32||s[i]>126);
				root->r->l=new Splay(s,s+n,root->r);
				root->r->update();
				root->update();
				break;
			case 'D'://Delete n
				scanf("elete %u",&n);
				root->r->nth(n+1)->splay(root->r);
				root->r->l->del();
				root->r->l=null;
				root->r->update();
				root->update();
				break;
			case 'R'://Rotate n
				scanf("otate %u",&n);
				root->r->nth(n+1)->splay(root->r);
				root->r->l->rev^=1;
				break;
			case 'G'://Get n
				scanf("et");
				putchar(root->r->nth(1)->c);
				putchar('\n');
				break;
			case 'P'://Prev
				scanf("rev");
				root->l->nth(root->l->size)->splay(root);
				break;
			case 'N'://Next
				scanf("ext");
				root->r->nth(1)->splay(root);
				break;
		}
	//puts("--------------------------------");system("editor");
}

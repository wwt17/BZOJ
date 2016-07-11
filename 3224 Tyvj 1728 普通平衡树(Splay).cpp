#include <cstdio>
#include <algorithm>
using namespace std;
struct Splay *null,*root;
struct Splay{
	Splay *l,*r,*pa; int data,cnt,size;
	Splay():l(null),r(null),pa(null){
	}
	Splay(Splay *_pa,int _data):l(null),r(null),pa(_pa),data(_data),cnt(1),size(1){
	}
	void update(){
		size=l->size+r->size+cnt;
	}
	#define x this
	void zig(){
		Splay *y=x->pa,*z=y->pa;
		(y==z->l?z->l:z->r)=x; x->pa=z;
		y->l=x->r; x->r->pa=y;
		x->r=y; y->pa=x;
		y->update();
	}
	void zag(){
		Splay *y=x->pa,*z=y->pa;
		(y==z->l?z->l:z->r)=x; x->pa=z;
		y->r=x->l; x->l->pa=y;
		x->l=y; y->pa=x;
		y->update();
	}
	void splay(Splay *&goal){
		if(this==null) return;
		Splay *y,*z,*top=goal->pa;
		while((y=x->pa)!=top)
			if((z=y->pa)==top)
				if(x==y->l) zig(); else zag();
			else
				if(y==z->l)
					if(x==y->l) y->zig(),zig();
					else zag(),zig();
				else
					if(x==y->r) y->zag(),zag();
					else zig(),zag();
		update();
		goal=x;
	}
	#undef x
	void ins(int k){
		Splay *x=this,*y=pa;
		while(x!=null){
			y=x;
			if(k<x->data) x=x->l; else
			if(k>x->data) x=x->r; else
			{ x->cnt++; return x->splay(root); }
		}
		return ((k<y->data?y->l:y->r)=new Splay(y,k))->splay(root);
	}
	void del(int k){
		Splay *x=this;
		while(x!=null)
			if(k<x->data) x=x->l; else
			if(k>x->data) x=x->r; else{
				if(!--x->cnt){
					Splay *y=x;
					if(x->l!=null){
						y->l->nth(y->l->size)->splay(y->l);
						x=y->l;
						(y->pa->l==y?y->pa->l:y->pa->r)=x; x->pa=y->pa;
						x->r=y->r; y->r->pa=x;
					} else
					if(x->r!=null){
						x=y->r;
						(y->pa->l==y?y->pa->l:y->pa->r)=x; x->pa=y->pa;
					} else{
						x=x->pa;
						(y->pa->l==y?y->pa->l:y->pa->r)=null;
					}
					delete y;
				}
				x->splay(root);
				return;
			}
	}
	Splay* find(int k){
		Splay *x=this;
		while(true)
			if(k<x->data) x=x->l; else
			if(k>x->data) x=x->r; else
			return x;
	}
	Splay* nth(int k){
		if(!size) return this;
		Splay *x=this;
		while(x!=null)
			if(k<=x->l->size) x=x->l; else
			if(k>x->l->size+x->cnt) k-=x->l->size+x->cnt,x=x->r; else
			return x;
	}
	Splay* pred(int k){
		Splay *x=this,*y=pa;
		while(x!=null){
			y=x;
			if(k<x->data) x=x->l; else
			if(k>x->data) x=x->r; else
				if(x->l!=null){
					x=x->l;
					while(x->r!=null) x=x->r;
					return x;
				}
				else{
					while(x==x->pa->l) x=x->pa;
					return x->pa;
				}
		}
		if(y->data<k) return y;
		while(y==y->pa->l) y=y->pa;
		return y->pa;
	}
	Splay* succ(int k){
		Splay *x=this,*y=pa;
		while(x!=null){
			y=x;
			if(k<x->data) x=x->l; else
			if(k>x->data) x=x->r; else
				if(x->r!=null){
					x=x->r;
					while(x->l!=null) x=x->l;
					return x;
				}
				else{
					while(x==x->pa->r) x=x->pa;
					return x->pa;
				}
		}
		if(y->data>k) return y;
		while(y==y->pa->r) y=y->pa;
		return y->pa;
	}
	void ptree(){
		if(this==null) return;
		static int tab=0;
		tab++;
		l->ptree();
		for(int i=0;i<tab-1;i++) printf("  ");
		printf("%d,%d size=%d\n",data,cnt,size);
		r->ptree();
		tab--;
	}
};
int main(){
	null=new Splay;
	null->l=null->r=null->pa=null;
	null->cnt=null->size=0;
	root=new Splay;
	root->data=0x80000000;
	root->size=root->cnt=0;
	root->r=new Splay;
	root->r->pa=root;
	root->r->data=0x7fffffff;
	root->r->size=root->r->cnt=0;
	int m,opt,x;
	scanf("%d",&m);
	while(
		/*
		puts("---------------"),
		root->ptree(),
		puts("---------------"),
		*/
		m--){
		scanf("%d%d",&opt,&x);
		switch(opt){
			case 1: root->ins(x); break;
			case 2: root->del(x); break;
			case 3: root->find(x)->splay(root);
				printf("%d\n",root->l->size+1); break;
			case 4: printf("%d\n",root->nth(x)->data); break;
			case 5: printf("%d\n",root->pred(x)->data); break;
			case 6: printf("%d\n",root->succ(x)->data); break;
		}
	}
	scanf("\n");
}

#include <cstdio>
#include <set>
using namespace std;
const int N=10001,C=1000001;
struct Splay *null;
struct Splay{
	Splay *l,*r,*pa; int size,a;
	Splay():l(null),r(null),pa(null),size(0),a(0){
	}
	Splay(Splay *_pa,int _a):l(null),r(null),pa(_pa),size(1),a(_a){
	}
	void update(){
		size=l->size+r->size+1;
	}
};
void zig(Splay* x){
	Splay *y=x->pa,*z=y->pa;
	x->pa=z; if(y==z->l) z->l=x; else z->r=x;
	x->r->pa=y; y->l=x->r;
	y->pa=x; x->r=y;
	y->update();
}
void zag(Splay* x){
	Splay *y=x->pa,*z=y->pa;
	x->pa=z; if(y==z->l) z->l=x; else z->r=x;
	x->l->pa=y; y->r=x->l;
	y->pa=x; x->l=y;
	y->update();
}
void splay(Splay*&root,Splay *x){
	if(x==null) return;
	Splay *y,*z,*top=root->pa;
	while((y=x->pa)!=top)
		if((z=y->pa)==top)
			if(x==y->l) zig(x); else zag(x);
		else
			if(y==z->l)
				if(x==y->l) zig(y),zig(x);
				else zag(x),zig(x);
			else
				if(x==y->r) zag(y),zag(x);
				else zig(x),zag(x);
	x->update();
	root=x;
}
void rank(Splay*&root,int k){
	Splay* x=root;
	while(true)
		if(k<x->l->size+1) x=x->l; else
		if(k>x->l->size+1) k-=x->l->size+1,x=x->r; else
		break;
	splay(root,x);
}
void insert(Splay*&root,int num){
	if(root==null){
		root=new Splay(null,num);
		return;
	}
	Splay *x=root,*y;
	while(x!=null){
		y=x;
		if(num<x->a) x=x->l; else
		if(num>x->a) x=x->r;
	}
	x=new Splay(y,num);
	if(num<y->a) y->l=x; else y->r=x;
	splay(root,x);
}
void remove(Splay*&root,int num){
	Splay *x,*y=root;
	while(y!=null)
		if(num<y->a) y=y->l; else
		if(num>y->a) y=y->r; else
		break;
	if(y==null) return;
	if(y->l!=null){
		x=y->l;
		rank(x,x->size);
		x->pa=y->pa;
		(y==root?root:y->pa->l==y?y->pa->l:y->pa->r)=x;
		x->r=y->r;
		y->r->pa=x;
	} else
	if(y->r!=null){
		x=y->r;
		rank(x,1);
		x->pa=y->pa;
		(y==root?root:y->pa->l==y?y->pa->l:y->pa->r)=x;
		x->l=y->l;
		y->l->pa=x;
	} else{
		if(y==root){
			delete y;
			root=null;
			return;
		}
		x=y->pa;
		if(y==x->l) x->l=null; else x->r=null;
	}
	delete y;
	splay(root,x);
}
int lesssum(Splay* root,int num){
	Splay *x=root;
	int ans=0;
	while(x!=null)
		if(num<x->a) x=x->l; else
		if(num>x->a) ans+=x->l->size+1,x=x->r; else
		return ans+=x->l->size;
	return ans;
}
int n,m,c[N];
set<int> s[C];
Splay *t[N];
int main(){
	null=new Splay;
	null->l=null->r=null->pa=null;
	null->size=0;
	scanf("%d%d",&n,&m);
	for(int col=1;col<C;col++) s[col].insert(-col),s[col].insert(n+col);
	for(int i=1;i<=n;i++) t[i]=null;
	int l,r,pos,col,ans,next,last;
	set<int>::iterator it,nextit,lastit;
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		last=*--s[c[i]].insert(i).first;
		for(int x=i;x<=n;x+=x&-x)
			insert(t[x],last);
	}
	while(m--)
		switch(getchar()){
			case 'Q':
				scanf("%d%d",&l,&r);
				ans=0;
				for(int x=r  ;x;x-=x&-x) ans+=lesssum(t[x],l);
				for(int x=l-1;x;x-=x&-x) ans-=lesssum(t[x],l);
				printf("%d\n",ans);
				break;
			case 'R':
				scanf("%d%d",&pos,&col);
				if(col==c[pos]) break;
				it=s[c[pos]].find(pos);
				nextit=it;
				lastit=it;
				next=*++nextit;
				last=*--lastit;
				for(int x=pos;x<=n;x+=x&-x)
					remove(t[x],last);
				for(int x=next;x<=n;x+=x&-x)
					remove(t[x],pos),
					insert(t[x],last);
				s[c[pos]].erase(it);
				c[pos]=col;
				it=s[col].insert(pos).first;
				nextit=it;
				lastit=it;
				next=*++nextit;
				last=*--lastit;
				for(int x=next;x<=n;x+=x&-x)
					remove(t[x],last),
					insert(t[x],pos);
				for(int x=pos;x<=n;x+=x&-x)
					insert(t[x],last);
				break;
			default: m++;
		}
}

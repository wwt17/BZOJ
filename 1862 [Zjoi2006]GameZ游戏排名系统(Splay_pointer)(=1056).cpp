#include <cstdio>
#include <cstring>
#define P 1000003
bool plined;
struct Splay *root,*null;
void nullinit();
struct Splay{
	Splay *l,*r,*pa; int size; char *Name; int Score;
	inline void update(){
		size=l->size+r->size+1;
	}
	#define x this
	void zig(){
		Splay *y=x->pa,*z=y->pa;
		x->pa=z; (y==z->l?z->l:z->r)=x;
		x->r->pa=y; y->l=x->r;
		y->pa=x; x->r=y;
		y->update();
	}
	void zag(){
		Splay *y=x->pa,*z=y->pa;
		x->pa=z; (y==z->l?z->l:z->r)=x;
		x->l->pa=y; y->r=x->l;
		y->pa=x; x->l=y;
		y->update();
	}
	void splay(){ splay(root); }
	void splay(Splay* &root){
		Splay *y,*z,*rtpa=root->pa;
		while((y=x->pa)!=rtpa){
			z=y->pa;
			if(z==rtpa) x==y->l?x->zig():x->zag(); else
			if(y==z->l) x==y->l?(y->zig(),x->zig()):(x->zag(),x->zig());
			       else x==y->r?(y->zag(),x->zag()):(x->zig(),x->zag());
		}
		update();
		root=x;
	}
	#undef x
	void ins(Splay* k){
		Splay *x=this,*y=x->pa;
		while(x!=null){
			y=x;
			x=k->Score>x->Score?x->l:x->r;
		}
		(k->Score>y->Score?y->l:y->r)=k;
		k->pa=y;
		k->splay();
	}
	Splay* cutl(){
		Splay *x=this,*y;
		while (x->l!=null) x=x->l;
		x->r->pa=x->pa; (x==x->pa->l?x->pa->l:x->pa->r)=x->r;
		for (y=x->pa;y!=null;y=y->pa) --y->size;
		x->r=x->pa=null;
		return x;
	}
	Splay* cutr(){
		Splay *x=this,*y;
		while (x->r!=null) x=x->r;
		x->l->pa=x->pa; (x==x->pa->l?x->pa->l:x->pa->r)=x->l;
		for (y=x->pa;y!=null;y=y->pa) --y->size;
		x->l=x->pa=null;
		return x;
	}
	void cut(){
		splay();
		root=(l!=null?l->cutr():r!=null?r->cutl():null);
		root->l=l; root->l->pa=root;
		root->r=r; root->r->pa=root;
		root->update();
		l=r=pa=null;
		size=1;
	}
	int Rank(){
		splay();
		return l->size+1;
	}
	Splay* No(int k){
		if(k>size) k=size+1;
		Splay* x=this;
		int mid;
		while (x!=null){
			mid=x->l->size+1;
			if (k<mid) x=x->l; else
			if (k>mid) x=x->r,k-=mid; else
				return x;
		}
		return null;
	}
	void List(const int rank,const int sum){
		root->No(rank-1)->splay(root);
		root->No(rank+sum)->splay(root->r);
		plined=false; root->r->l->pline(); putchar('\n');
	}
	void pline(){
		if (this==null) return;
		l->pline();
		plined?putchar(' '):plined=true;
		printf("%s",Name);
		r->pline();
	}
} spl[250000],*newspl=spl;
#define newSplay (*newspl=(Splay){null,null,null,1,0,0},newspl++)
inline void nullinit(){
	null->l=null->r=null->pa=null; null->size=null->Score=0; null->Name="null";
}
Splay *h[P];
typedef char NameType[12];
NameType Names[250001],*newName=Names;
int main(){
	int n; scanf("%d",&n);
	char opt,*i; int v;
	null=new Splay; nullinit(); root=null;
	Splay *tmp,*tt=new Splay;
	tt->size=-1;
	tmp=newSplay;
	tmp->size=0;
	tmp->Score=0x7FFFFFFF;
	tmp->l=tt;
	root->ins(tmp);
	tmp=newSplay;
	tmp->size=0;
	tmp->Score=-1;
	tmp->r=tt;
	root->ins(tmp);
	while(n--){
		getchar(); opt=getchar();
		if(opt=='+'){
			scanf("%s",newName); for(v=0,i=*newName;*i;++i) v=(v*27+*i)%P;
			while(h[v]&&strcmp(h[v]->Name,*newName)) if(++v==P) v=0;
			if(h[v]) h[v]->cut();
			else h[v]=newSplay;
			h[v]->Name=*newName++;
			scanf("%d",&h[v]->Score);
			root->ins(h[v]);
		}else
		if(opt=='?'&&scanf("%d",&v)!=1){
			scanf("%s",newName); for(v=0,i=*newName;*i;++i) v=(v*27+*i)%P;
			while(h[v]&&strcmp(h[v]->Name,*newName)) if(++v==P) v=0;
			printf("%d\n",h[v]->Rank());
		}else
			root->List(v,10);
	}
}

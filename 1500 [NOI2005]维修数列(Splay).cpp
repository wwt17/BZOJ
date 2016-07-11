#include <cstdio>
#include <algorithm>
#define MAX(a,b) std::max(a,b)
#define MAX3(a,b,c) std::max(std::max(a,b),c)
#define swap(a,b) std::swap(a,b)
struct Splay *root,*null,*begin,*end;
void nullinit();
struct Splay{
	Splay *l,*r,*pa;
	int size,num,cov,sum,max,maxl,maxr;
	bool covered,reversed;
	Splay():l(null),r(null),pa(null),
		size(1),num(-100000000),sum(0),max(-100000000),maxl(-100000000),maxr(-100000000),
		covered(false),reversed(false){
	}
	Splay(int* st,int* en):pa(null),covered(false),reversed(false){
		/*
		if(st>=en){
			new(this) Splay();
			return;
		}
		*/
		int* mid=st+((en-st)>>1);
		num=*mid;
		l=st<mid?new Splay(st,mid):null;
		r=mid+1<en?new Splay(mid+1,en):null;
		l->pa=r->pa=this;
		update();
	}
	inline void update(){
		size=l->size+1+r->size;
		sum=l->sum+(this==begin||this==end?0:num)+r->sum;
		max=MAX3(l->max,r->max,(l->maxr>0?l->maxr:0)+num+(r->maxl>0?r->maxl:0));
		maxl=MAX(l->maxl,l->sum+num+(r->maxl>0?r->maxl:0));
		maxr=MAX(r->maxr,r->sum+num+(l->maxr>0?l->maxr:0));
	}
	inline void down(){
		if(reversed){
			l->reverse();
			r->reverse();
			reversed=false;
		}
		if(covered){
			l->cover(cov);
			r->cover(cov);
			covered=false;
		}
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
	void correct(){ if(pa!=null) pa->correct(); down(); }
	void splay(){ splay(root); }
	void splay(Splay* &goal){
		correct();
		Splay *y,*z,*top=goal->pa;
		while((y=pa)!=top)
			if((z=y->pa)==top) if(x==y->l) zig(); else zag(); else
			if(y==z->l) if(x==y->l) y->zig(),zig(); else zag(),zig();
			       else if(x==y->r) y->zag(),zag(); else zig(),zag();
		update();
		goal=x;
	}
	#undef x
	Splay* select(int left,int right){
		root->No(left-1)->splay(root);
		root->No(right+1)->splay(root->r);
		return root->r->l;
	}
	void ins(const int posi,Splay* k){
		select(posi+1,posi);
		root->r->l=k;
		k->pa=root->r;
		root->r->update();
		root->update();
	}
	void del(){
		if(this==null) return;
		l->del();
		r->del();
		delete this;
	}
	void del(const int posi,const int tot){
		select(posi,posi+tot-1)->del();
		root->r->l=null;
		root->r->update();
		root->update();
	}
	void cover(const int c){
		if(this==null) return;
		covered=true;
		num=cov=c;
		sum=cov*size;
		max=maxl=maxr=c>0?sum:c;
	}
	void reverse(){
		reversed^=1;
		swap(l,r);
		swap(maxl,maxr);
	}
	void cover(const int posi,const int tot,const int c){
		select(posi,posi+tot-1)->cover(c);
		root->r->update();
		root->update();
	}
	void reverse(const int posi,const int tot){
		select(posi,posi+tot-1)->reverse();
		root->r->update();
		root->update();
	}
	int query_sum(const int posi,const int tot){
		return select(posi,posi+tot-1)->sum;
	}
	int query_max(const int posi,const int tot){
		return select(posi,posi+tot-1)->max;
	}
	Splay* No(int k){
		Splay* x=this;
		int mid;
		while(x!=null){
			x->down();
			mid=x->l->size+1;
			if(k<mid) x=x->l; else
			if(k>mid) x=x->r,k-=mid; else
				return x;
		}
		return null;
	}
	/*
	void pline();
	void ptree(){
		puts("------------------------------");
		ptree(0);
		puts("------------------------------");
	}
	void ptree(int tab);
	*/
};
/*
void Splay::pline(){
	if(this==null) return;
	(reversed?r:l)->pline();
	printf("%3d",num);
	(reversed?l:r)->pline();
}
void pline(){
	root->pline();
	putchar('\n');
}
void Splay::ptree(int tab){
	if (this==null) return;
	l->ptree(tab+1);
	printf("%2d ",num);
	for(int t=tab;t;t--) printf("  ");
	printf("num=%d size=%d sum=%d max=%d maxl=%d maxr=%d",
		num,size,sum,max,maxl,maxr);
	if(covered) printf(" cov=%d",cov);
	if(reversed) printf(" reversed");
	putchar('\n');
	r->ptree(tab+1);
}
*/
inline void nullinit(){
	null->l=null->r=null->pa=null; null->size=null->sum=0;
}
int c[500000],top;
int main(){
	int n,m; scanf("%u%u",&n,&m);
	null=new Splay; nullinit();
	Splay *tt=new Splay;
	tt->size=-1;
	root=begin=new Splay;
	begin->size=0;
	begin->l=tt;
	begin->r=end=new Splay;
	end->pa=begin;
	end->size=0;
	end->r=tt;
	for(top=0;top<n;top++) scanf("%d",c+top);
	root->ins(0,new Splay(c,c+n));
	int posi,tot;
	while(m--) switch(scanf("\n"),getchar(),getchar(),getchar()){
		case 'S'://INSERT
			scanf("ERT %u %u",&posi,&tot);
			for(top=0;top<tot;top++) scanf("%d",c+top);
			root->ins(posi,new Splay(c,c+tot));
			break;
		case 'L'://DELETE
			scanf("ETE %u %u",&posi,&tot);
			root->del(posi,tot);
			break;
		case 'K'://MAKE-SAME
			scanf("E-SAME %u %u %d",&posi,&tot,c);
			root->cover(posi,tot,*c);
			break;
		case 'V'://REVERSE
			scanf("ERSE %u %u",&posi,&tot);
			root->reverse(posi,tot);
			break;
		case 'T'://GET-SUM
			scanf("-SUM %u %u",&posi,&tot);
			printf("%d\n",root->query_sum(posi,tot));
			break;
		case 'X'://MAX-SUM
			scanf("-SUM");
			printf("%d\n",root->max);
	}
	//scanf("%u");
}

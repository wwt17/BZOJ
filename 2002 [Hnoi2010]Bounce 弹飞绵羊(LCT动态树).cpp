#include <cstdio>
#include <cstdlib>
#define Ps system("pause")
struct LCT *null;
struct LCT{
	LCT *l,*r,*pa; bool rev; int size;
	void init(){
		l=r=pa=null; rev=false; size=1;
	}
	inline void update(){
		size=l->size+r->size+1;
	}
	inline bool istop(){
		return this==null||pa==null||pa->l!=this&&pa->r!=this;
	}
	inline void reverse(){
		rev^=1; LCT* tmp=l;l=r;r=tmp;
	}
	inline void down(){
		if(rev){ rev=false; l->reverse(); r->reverse(); }
	}
	void correct(){
		if(!istop()) pa->correct(); down();
	}
	LCT* top(){
		splay(); LCT *x=this; while(x->l) x=x->l,x->down(); return x;
	}
	LCT* access(){
		LCT *x=this,*y=null;
		while(x!=null){ x->splay(); x->r=y; x->update(); y=x; x=x->pa; }
		return y;
	}
	#define x this
	void zig(){
		LCT *y=x->pa,*z=y->pa;
		x->pa=z; y==z->l?(z->l=x):y==z->r?(z->r=x):0;
		x->r->pa=y; y->l=x->r;
		y->pa=x; x->r=y;
		y->update();
	}
	void zag(){
		LCT *y=x->pa,*z=y->pa;
		x->pa=z; y==z->l?(z->l=x):y==z->r?(z->r=x):0;
		x->l->pa=y; y->r=x->l;
		y->pa=x; x->l=y;
		y->update();
	}
	void splay(){
		LCT *y;
		while(!istop()){
			y=x->pa;
			if(y->istop())  x==y->l?zig():zag(); else
			if(y==y->pa->l) x==y->l?(y->zig(),x->zig()):(x->zag(),x->zig());
			           else x==y->r?(y->zag(),x->zag()):(x->zig(),x->zag());
		}
		update();
	}
	#undef x
	void Cut(){
		access(); splay(); l->pa=null; l=null; update();
	}
	void Connect_to(LCT* y){
		access(); splay(); reverse(); pa=y;
	}
	unsigned Depth(){
		return access()->size;
	}
} eqp[200000];
void nullinit(){ null->l=null->r=null->pa=null; null->size=0; }
int main(){
	null=new LCT; nullinit();
	unsigned n,m,i,j,k;
	scanf("%u",&n);
	for(i=0;i<n;++i) eqp[i].init();
	for(i=0;i<n;++i){
		scanf("%u",&k);
		if(i+k<n)
			eqp[i].Connect_to(eqp+(i+k));
	}
	scanf("%u",&m);
	while(m--)
		if(scanf("%u%u",&i,&j),i==1)
			printf("%u\n",eqp[j].Depth());
		else{
			scanf("%u",&k);
			eqp[j].Cut();
			if(j+k<n) eqp[j].Connect_to(eqp+(j+k));
		}
	Ps;
}

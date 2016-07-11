#include <cstdio>
#include <algorithm>
using namespace std;

const int N=100005;

int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}

int n;

struct node *null;
struct node{
	node *l,*r,*pa; int size,sum,val; node *lis;
	node *L,*R,*Pa; int Size;
	void init(int s){
		l=r=pa=null; size=s;
		L=R=Pa=null; Size=s;
	}
	void Update(){
		if(this==null) return;
		Size=L->Size+R->Size+1;
	}
	bool Istop(){
		return Pa==null||Pa->L!=this&&Pa->R!=this;
	}
	void update(){
		if(this==null) return;
		size=l->size+r->size+1;
		sum=l->sum+r->sum+val;
	}
	bool istop(){
		return pa==null||pa->l!=this&&pa->r!=this;
	}
	#define x this
	void zig(){
		node *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->l=x->r;
		x->r->pa=y;
		x->r=y;
		y->pa=x;
		y->update();
	}
	void zag(){
		node *y=x->pa,*z=y->pa;
		if(y==z->l) z->l=x; else
		if(y==z->r) z->r=x;
		x->pa=z;
		y->r=x->l;
		x->l->pa=y;
		x->l=y;
		y->pa=x;
		y->update();
	}
	void Zig(){
		node *y=x->Pa,*z=y->Pa;
		if(y==z->L) z->L=x; else
		if(y==z->R) z->R=x;
		x->Pa=z;
		y->L=x->R;
		x->R->Pa=y;
		x->R=y;
		y->Pa=x;
		y->Update();
	}
	void Zag(){
		node *y=x->Pa,*z=y->Pa;
		if(y==z->L) z->L=x; else
		if(y==z->R) z->R=x;
		x->Pa=z;
		y->R=x->L;
		x->L->Pa=y;
		x->L=y;
		y->Pa=x;
		y->Update();
	}
	#undef x
} V[N];

void splay(node *x){
	while(!x->istop()){
		node *y=x->pa;
		if(y->istop())
			if(x==y->l) x->zig(); else x->zag();
		else
			if(y==y->pa->l)
				if(x==y->l)
					y->zig(),x->zig();
				else
					x->zag(),x->zig();
			else
				if(x==y->r)
					y->zag(),x->zag();
				else
					x->zig(),x->zag();
	}
	x->update();
}

void Splay(node *x){
	while(!x->Istop()){
		node *y=x->Pa;
		if(y->Istop())
			if(x==y->L) x->Zig(); else x->Zag();
		else
			if(y==y->Pa->L)
				if(x==y->L)
					y->Zig(),x->Zig();
				else
					x->Zag(),x->Zig();
			else
				if(x==y->R)
					y->Zag(),x->Zag();
				else
					x->Zig(),x->Zag();
	}
	x->Update();
}

node* access(node *x){
	node *y=null,*last=null;
	while(x!=null){
		splay(x);
		x->r->pa=null;
		if(y!=null){
			Splay(y);
			x->lis=y;
			x->val=x->lis->L->Size+1;
		}
		else{
			x->val=0;
		}
		x->r=y;
		y->pa=x;
		x->update();
		last=x;
		while(x->l!=null) x=x->l;
		splay(x);
		Splay(x);
		y=x;
		x=x->Pa;
	}
	return last;
}

node* Kth(node *x,int k){
	for(;;){
		if(k<x->L->Size+1)
			x=x->L;
		else
		if(k>x->L->Size+1)
			k-=x->L->Size+1,x=x->R;
		else
			return x;
	}
}

typedef pair<node*,node*> pnn;

pnn Split(node *cur,int k){
	if(k==0) return pnn(null,cur);
	Splay(cur=Kth(cur,k));
	pnn tmp(cur,cur->R);
	cur->R->Pa=null;
	cur->R=null;
	cur->Update();
	return tmp;
}

node* Merge(node *u,node *v){
	if(u==null) return v;
	if(v==null) return u;
	for(;u->R!=null;u=u->R);
	Splay(u);
	u->R=v;
	v->Pa=u;
	u->Update();
	return u;
}

node* Build(node** beg,node** end){
	if(beg==end) return null;
	node **mid=beg+(end-beg>>1);
	(*mid)->L=Build(beg,mid);
	(*mid)->R=Build(mid+1,end);
	(*mid)->L->Pa=*mid;
	(*mid)->R->Pa=*mid;
	(*mid)->Update();
	return *mid;
}

node *seq[N];

int main(){
	n=getint();
	int m=getint();
	null=V;
	null->init(0);
	for(node *u=V+1;u<=V+n;u++) u->init(1);
	for(node *u=V+1;u<=V+n;u++){
		int k=getint();
		for(int i=0;i<k;i++){
			seq[i]=V+getint();
		}
		u->lis=Build(seq,seq+k);
		u->lis->Pa=u;
	}
	while(m--){
		int type=getint();
		if(type==1){
			node *x=V+getint();
			int p=getint(),c=getint();
			node *y=V+getint();
			int q=getint();
			access(x);
			if(x==y&&q>=p+c-1) q-=c;
			pnn tmp=Split(x->lis,p-1);
			x->lis=tmp.first;
			node *res=tmp.second;
			tmp=Split(res,c);
			x->lis=Merge(x->lis,tmp.second);
			x->lis->Pa=x;
			res=tmp.first;
			access(y);
			tmp=Split(y->lis,q);
			y->lis=Merge(Merge(tmp.first,res),tmp.second);
			y->lis->Pa=y;
		}
		else
		if(type==2){
			node *x=V+getint(),*y=V+getint();
			if(x==y){
				puts("0");
				continue;
			}
			access(x);
			node *z=access(y);
			access(z);
			if(z==y){
				splay(x);
				printf("%d\n",x->size-1);
			}
			else
			if(z==x){
				splay(y);
				printf("%d\n",y->size-1);
			}
			else{
				access(z);
				splay(x);
				splay(y);
				printf("%d\n",x->size+y->size-2);
			}
		}
		else
		if(type==3){
			node *x=V+getint();
			access(x);
			splay(x);
			printf("%d\n",x->l->sum);
		}
	}
}

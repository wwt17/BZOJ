#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=80001,logN=17;

int n,m,t,logn,L[N],*R;

struct tree{
	tree *l,*r; int sum;
	tree():l(NULL),r(NULL),sum(0){
	}
	/*
	~tree(){
		if(l) delete l;
		if(r) delete r;
	}
	*/
};
int *num,k;
tree* insert(tree* root,int* begin,int* end){
	tree* ret=root?new tree(*root):new tree;
	ret->sum++;
	if(end-begin>1){
		int* mid=begin+(end-begin)/2;
		if(num<mid)
			ret->l=insert(ret->l,begin,mid);
		else
			ret->r=insert(ret->r,mid,end);
	}
	return ret;
}
int query(tree* A,tree* B,tree* C,tree* D){
	int *begin=L,*end=R;
	while(end-begin>1){
		int* mid=begin+(end-begin)/2;
		int midk=
		 (A&&A->l?A->l->sum:0)
		-(B&&B->l?B->l->sum:0)
		+(C&&C->l?C->l->sum:0)
		-(D&&D->l?D->l->sum:0);
		if(k<=midk){
			if(A) A=A->l;
			if(B) B=B->l;
			if(C) C=C->l;
			if(D) D=D->l;
			end=mid;
		}
		else{
			if(A) A=A->r;
			if(B) B=B->r;
			if(C) C=C->r;
			if(D) D=D->r;
			k-=midk;
			begin=mid;
		}
	}
	return *begin;
}

struct node;
struct edge{
	node* ed; edge* next;
} E[N<<1],*newE=E;

struct node{
	edge* son;
	node *pa[logN],*belong;
	int w,size,depth;
	tree* f;
	void build(){
		depth=pa[0]->depth+1;
		for(int j=1;j<logn;j++) pa[j]=pa[j-1]->pa[j-1];
		delete f;
		num=lower_bound(L,R,w);
		f=insert(pa[0]->f,L,R);
		size=1;
		for(edge* e=son;e;e=e->next) if(e->ed!=pa[0]){
			e->ed->pa[0]=this;
			e->ed->belong=belong;
			e->ed->build();
			size+=e->ed->size;
		}
	}
} V[N];

node* LCA(node* u,node* v){
	for(int j=logn;j--;) if(u->pa[j]->depth>=v->depth)
		u=u->pa[j];
	for(int j=logn;j--;) if(v->pa[j]->depth>=u->depth)
		v=v->pa[j];
	if(u==v) return u;
	for(int j=logn;j--;) if(u->pa[j]!=v->pa[j])
		u=u->pa[j],v=v->pa[j];
	return u->pa[0];
}

int main(){
	scanf("%*d%d%d%d",&n,&m,&t);
	for(logn=0;1<<logn<n;logn++) V->pa[logn]=V;
	V->depth=0;
	for(int i=1;i<=n;i++) scanf("%d",&V[i].w),L[i-1]=V[i].w;
	sort(L,L+n);
	R=unique(L,L+n);
	while(m--){
		static int x,y;
		scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int i=1;i<=n;i++) if(!V[i].pa[0]){
		V[i].pa[0]=V;
		V[i].belong=V+i;
		V[i].build();
	}
	int lastans=0;
	while(t--){
		static int x,y;
		static char opt;
		scanf("\n%c%d%d",&opt,&x,&y);
		node *u=V+(x^=lastans),*v=V+(y^=lastans);
		if(opt=='Q'){
			scanf("%d",&k);
			k^=lastans;
			node* lca=LCA(u,v);
			printf("%d\n",lastans=query(u->f,lca->pa[0]->f,v->f,lca->f));
		}
		else{
			*newE=(edge){v,u->son},u->son=newE++;
			*newE=(edge){u,v->son},v->son=newE++;
			if(u->belong->size<v->belong->size){
				u->pa[0]=v;
				u->belong=v->belong;
				u->build();
				for(node *i=v;i!=V;i=i->pa[0]) i->size+=u->size;
			}
			else{
				v->pa[0]=u;
				v->belong=u->belong;
				v->build();
				for(node *i=u;i!=V;i=i->pa[0]) i->size+=v->size;
			}
		}
	}
}

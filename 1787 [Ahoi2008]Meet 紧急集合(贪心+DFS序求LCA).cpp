#include <cstdio>
const int N=500001;
int n,m;
struct node *t[1<<22];
struct edge{
	node *ed; edge *next;
} E[N<<1],*newE=E;
int Base,len=1;
struct node{
	edge *son; node *pa;
	int h,l,r;
	void DFS(){
		t[Base+(l=len++)]=this;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->h=h+1;
			e->ed->DFS();
		}
		t[Base+(r=len++)]=this;
	}
} V[N];
inline node *LCA(node *A,node *B){
	node *ret=V;
	int l=A->l,r=B->l;
	if(l>r){ int tmp=l; l=r; r=tmp; }
	if(r-l<=1) return A->h<B->h?A:B;
	for(l+=Base,r+=Base;l^r^1;l>>=1,r>>=1){
		if(!(l&1)) if(t[l^1]->h<ret->h) ret=t[l^1];
		if(  r&1 ) if(t[r^1]->h<ret->h) ret=t[r^1];
	}
	return ret->pa;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	for(Base=1;Base<=n*2;Base<<=1);
	V->h=n;
	for(int i=0;i<=Base+n*2+1;i++) t[i]=V;
	V[1].pa=V;
	V[1].DFS();
	for(int l=Base>>1,r=(Base+len)>>1;l+1<r;l>>=1,r>>=1)
		for(int i=l+1;i<r;i++)
			t[i]=t[i<<1]->h<t[i<<1|1]->h?t[i<<1]:t[i<<1|1];
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		node
			*ab=LCA(V+a,V+b),
			*bc=LCA(V+b,V+c),
			*ac=LCA(V+a,V+c);
		if(ab==ac) printf("%d",bc-V); else
		if(ab==bc) printf("%d",ac-V); else
		if(ac==bc) printf("%d",ab-V);
		printf(" %d\n",V[a].h+V[b].h+V[c].h-ab->h-bc->h-ac->h);
	}
}

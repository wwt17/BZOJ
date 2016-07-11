#include <cstdio>
#define N 100001
struct node;
struct edge{
	node* ed; edge* next; short l;
} E[N<<1],*newE=E;
struct node{
	edge* son; node* pa; int sum; long long sub;
	void init();
	void DFS(const long long cost);
} V[N];
int n,i; long long Ans=0x7FFFFFFFFFFFFFFFLL;
void node::init(){
	node* v;
	for(edge* e=son;e;e=e->next) if((v=e->ed)!=pa){
		v->pa=this;
		v->init();
		sum+=v->sum;
		sub+=v->sub+(long long)v->sum*e->l;
	}
}
void node::DFS(const long long cost){
	if(Ans>cost+sub) Ans=cost+sub;
	node* v;
	for(edge* e=son;e;e=e->next) if((v=e->ed)!=pa)
		v->DFS(cost+sub-v->sub+(long long)(V[1].sum-(v->sum<<1))*e->l);
}
int main(){
	scanf("%u",&n);
	for(i=1;i<=n;i++) scanf("%d",&V[i].sum);
	for(i=1;i<n;i++){
		static int a,b,l;
		scanf("%u%u%d",&a,&b,&l);
		*newE=(edge){V+b,V[a].son,l}; V[a].son=newE++;
		*newE=(edge){V+a,V[b].son,l}; V[b].son=newE++;
	}
	V[1].init();
	V[1].DFS(0);
	printf("%lld\n",Ans);
}

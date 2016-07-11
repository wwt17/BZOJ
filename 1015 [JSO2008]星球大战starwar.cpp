#include <cstdio>
#define sizeM 200005
#define sizeN 2*sizeM
int N,M,S,d[sizeN],i,ans[sizeN+1];
struct node *base;
struct edge{
	node* ed;
	edge* next;
	edge(node* _ed,edge* _next):ed(_ed),next(_next){}
};
struct node{
	edge* son;
	node* belong;
	bool exist;
	node():son(NULL),belong(this),exist(true){}
	inline void addedge(node* ed){
		edge* e=new edge(ed,son);
		son=e;
	}
	void renew(){
		if (this==belong) return;
		belong->renew();
		belong=belong->belong;
	}
	inline bool link(node* ed){
		renew();ed->renew();
		if (belong!=ed->belong){
			ed->belong->belong=belong;
			return true;
		}
		return false;
	}
	int recover(){
		exist=true;
		int ret=1;
		for (edge* e=son;e;e=e->next) if (e->ed->exist)
			ret-=link(e->ed);
		return ret;
	}
};
int main(){
	scanf("%d%d",&N,&M);
	node v[N];base=v;
	int X,Y;
	while (M--){
		scanf("%d%d",&X,&Y);
		v[X].addedge(v+Y);
		v[Y].addedge(v+X);
	}
	scanf("%d",&S);
	for (i=0;i<S;++i) scanf("%d",&d[i]),v[d[i]].exist=false;
	ans[S]=0;
	for (i=0;i<N;++i) if (v[i].exist) ans[S]+=v[i].recover();
	for (i=S-1;i>=0;--i)
		ans[i]=ans[i+1]+v[d[i]].recover();
	for (i=0;i<=S;++i) printf("%d\n",ans[i]);
}

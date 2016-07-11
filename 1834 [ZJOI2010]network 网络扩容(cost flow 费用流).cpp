#define sizeV 1001
#define sizeE 20005
#include <cstdio>
#include <queue>
#define inf 0x7FFFFFFF
inline int min(const int a,const int b){return a<b?a:b;}
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node *pre,*ed; edge* next; int cap,cost;
} E[sizeE],*Es=E;
struct node{
	edge* son; int dist,flow; edge* fro;
	node():son(NULL){}
};
inline void addedge(node* u,node* v,const int cap,const int cost){
	*Es=(edge){u,v,u->son,cap,cost},u->son=Es++;
	*Es=(edge){v,u,v->son,0,-cost},v->son=Es++;
}
//define graph
node *S,*T,V[sizeV];
int u[5001],v[5001],W[5001],N;
inline void print(){
	for (node* v=V;v<=V+N;++v){
		printf("%d:",v-V);
		for (edge* e=v->son;e;e=e->next) if (e->cap)
			printf(" %d",e->cap);
		putchar('\n');
	}
}
int main(){
	//make graph
	int M,K,i,m,C;
	scanf("%d%d%d",&N,&M,&K);
	S=V+1,T=V+N;
	for (m=1;m<=M;++m){
		scanf("%d%d%d%d",u+m,v+m,&C,W+m);
		addedge(V+u[m],V+v[m],C,0);
	}
	//calc flow
	int ans=0;
	for(;;){
		std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for (i=1;i<=N;++i) V[i].dist=inf;
		S->dist=0;S->fro=NULL;
		for (q.push(S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					{y->fro=e;if(y->dist<T->dist)q.push(y);}
		if (T->dist==inf) break;
		int c=inf;
		for (e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		ans+=c;
		for (e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c;
	}
	//print ans
	printf("%d ",ans);
	//calc cost flow
	int Ans=0;
	for (m=1;m<=M;++m)
		addedge(V+u[m],V+v[m],K,W[m]);
	addedge(V,S,K,0);S=V;
	for(;;){
		std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for (i=1;i<=N;++i) V[i].dist=inf;
		S->dist=0;S->fro=NULL;
		for (q.push(S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					{y->fro=e;if(y->dist<T->dist)q.push(y);}
		if (T->dist==inf) break;
		int c=inf;
		for (e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for (e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d\n",Ans);
}

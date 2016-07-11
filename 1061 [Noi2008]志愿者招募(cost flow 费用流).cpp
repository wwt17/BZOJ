//http://www.byvoid.com/zhs/blog/noi-2008-employee/
#include <cstdio>
#include <queue>
#define sizeE 24002
#define inf 0x7fffffff
inline int min(const int a,const int b){return a<b?a:b;}
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node *pre,*ed; edge* next; int cap,cost;
} E[sizeE]; int Es=0;
struct node{
	edge* son; int dist,flow; edge* fro;
	node():son(NULL){}
};
inline void addedge(node* u,node* v,const int cap,const int cost){
	E[Es++]=(edge){u,v,u->son,cap,cost},u->son=E+Es-1;
	E[Es++]=(edge){v,u,v->son,0,-cost},v->son=E+Es-1;
}
int main(){
	int N,M,i;
	scanf("%d%d",&N,&M);
	node V[N+1],S,T;
	int demond[N+2];
	demond[0]=0;
	for (i=1;i<=N;++i) scanf("%d",demond+i);
	demond[N+1]=0;
	for (i=0;i<=N;++i){
		int tmp=demond[i+1]-demond[i];
		if (tmp>=0) addedge(&S,V+i,tmp,0);
		else        addedge(V+i,&T,-tmp,0);
	}
	int Si,Ti,Ci;
	while (M--){
		scanf("%d%d%d",&Si,&Ti,&Ci);
		addedge(V+Si-1,V+Ti,inf,Ci);
	}
	for (i=0;i<N;++i) addedge(V+i+1,V+i,inf,0);
	
	int Ans=0;
	S.dist=0;S.fro=NULL;
	for(;;){
		std::queue<node*> q; node *x,*y; edge *e;
		for (i=0;i<=N;++i) V[i].dist=inf,V[i].fro=NULL; T.dist=inf,T.fro=NULL;
		for (q.push(&S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					y->fro=e,q.push(y);
		if (T.dist==inf) break;
		int c=inf;
		for (e=T.fro;e;e=e->pre->fro) mini(c,e->cap);
		for (e=T.fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	printf("%d\n",Ans);
}

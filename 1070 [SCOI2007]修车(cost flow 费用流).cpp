#include <cstdio>
#include <queue>
#define sizeM 10
#define sizeN 61
#define sizeE 66010
#define inf 0x7FFFFFFF
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
//define graph
node S,T,car[sizeN],worker[sizeM][sizeN];
int main(){
	//make graph
	int M,N,i,j,ii;scanf("%d%d",&M,&N);
	for (i=1;i<=N;++i) addedge(&S,car+i,1,0);
	int time;
	for (i=1;i<=N;++i)
		for (j=1;j<=M;++j){
			scanf("%d",&time);
			for (ii=1;ii<=N;++ii)
				addedge(car+i,&worker[j][ii],1,time*ii);
		}
	for (j=1;j<=M;++j)
		for (ii=1;ii<=N;++ii)
			addedge(&worker[j][ii],&T,1,0);
	//calc cost flow
	int Ans=0;
	S.dist=0;S.fro=NULL;
	for(;;){
		std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for (i=1;i<=N;++i) car[i].dist=inf;
		for (j=1;j<=M;++j) for (ii=1;ii<=N;++ii) worker[j][ii].dist=inf;
		T.dist=inf;
		for (q.push(&S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					{y->fro=e;if (y->dist<T.dist) q.push(y);}
		if (T.dist==inf) break;
		int c=inf;
		for (e=T.fro;e;e=e->pre->fro) mini(c,e->cap);
		for (e=T.fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%.2f\n",(float)Ans/N);
}

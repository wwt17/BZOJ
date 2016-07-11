#include <cstdio>
#include <queue>
#define sizeV 201
#define sizeE 40410
#define Source (gout+1)
#define Sink (goin+N)
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
node *S,*T,goin[sizeV],gout[sizeV];
int main(){
	//make graph
	int N,M,i,a,b,c;
	scanf("%d%d",&N,&M);
	while (M--){
		scanf("%d%d%d",&a,&b,&c);
		addedge(gout+a,goin+b,1,c);
	}
	for (i=1;i<=N;++i) addedge(goin+i,gout+i,1,0);
	S=Source,T=Sink;
	//calc cost flow
	int ans=0,Ans=0;
	for(;;++ans){
		std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for (i=1;i<=N;++i) goin[i].dist=inf,gout[i].dist=inf;
		S->dist=0;S->fro=NULL;
		for (q.push(S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost)&&y->dist<T->dist)
					y->fro=e,q.push(y);
		if (T->dist==inf) break;
		int c=inf;
		for (e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for (e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d %d\n",ans,Ans);
}

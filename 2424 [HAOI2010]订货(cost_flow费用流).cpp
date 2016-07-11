#include <cstdio>
#include <queue>
const int inf=0x7FFFFFFF,N=55,M=N*3;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
int n,m,s;
struct node;
struct edge{
	node *pre,*ed; edge *next; int cap,cost;
} E[M<<1],*newE=E;
struct node{
	edge *son; int dist,flow; edge *fro; bool inq;
	node():son(NULL){}
};
inline void addedge(node *u,node *v,const int cap=inf,const int cost=0){
	*newE=(edge){u,v,u->son,cap, cost},u->son=newE++;
	*newE=(edge){v,u,v->son,  0,-cost},v->son=newE++;
}
//define graph
node S[2],*T=S+1,V[N];
int main(){
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++) addedge(V+i,V+i+1,s,m);
	for(int i=1;i<=n;i++){
		static int U; scanf("%d",&U);
		addedge(V+i,T,U);
	}
	for(int i=1;i<=n;i++){
		static int d; scanf("%d",&d);
		addedge(S,V+i,inf,d);
	}
	//calc cost flow
	int Ans=0;
	for(;;){
		std::queue<node*> q; node *u,*v; edge *e;
		//clear
		for(int i=1;i<=n;++i) V[i].dist=inf;
		S->dist=0;S->fro=NULL; T->dist=inf;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),u->inq=false)
			for(e=(u=q.front())->son;e;e=e->next)
				if(e->cap&&mini((v=e->ed)->dist,u->dist+e->cost))
					{ v->fro=e; if(!v->inq) q.push(v),v->inq=true; }
		if(T->dist==inf) break;
		int c=inf;
		for(e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for(e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d\n",Ans);
}

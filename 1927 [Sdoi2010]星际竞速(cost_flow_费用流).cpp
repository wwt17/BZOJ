#include <cstdio>
#include <queue>
const int inf=0x7FFFFFFF,N=801,M=N*3+15000;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
int n,m;
struct node;
struct edge{
	node *pre,*ed; edge *next; int cap,cost;
} E[M<<1],*newE=E;
struct node{
	edge *son; int dist,flow; edge *fro; bool inq;
	node():son(NULL){}
};
inline void addedge(node *u,node *v,const int cap,const int cost){
	*newE=(edge){u,v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){v,u,v->son,0,-cost},v->son=newE++;
}
//define graph
node *S,*T,V[N][2];
int main(){
	//make graph
	scanf("%u%u",&n,&m);
	S=new node,T=new node;
	for(int i=1;i<=n;i++){
		int a; scanf("%d",&a);
		addedge(S,&V[i][1],1,a);
		addedge(S,&V[i][0],1,0);
		addedge(&V[i][1],T,1,0);
	}
	while(m--){
		int u,v,w;
		scanf("%u%u%d",&u,&v,&w);
		if(u>v) u^=v,v^=u,u^=v;
		addedge(&V[u][0],&V[v][1],1,w);
	}
	//calc cost flow
	int Ans=0;
	for(;;){
		std::queue<node*> q; node *u,*v; edge *e;
		//clear
		for(int i=1;i<=n;++i) V[i][0].dist=V[i][1].dist=inf;
		S->dist=0;S->fro=NULL; T->dist=inf;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),u->inq=false)
			for(e=(u=q.front())->son;e;e=e->next)
				if(e->cap&&mini((v=e->ed)->dist,u->dist+e->cost))
					{ v->fro=e; if(!v->inq&&v->dist<T->dist) q.push(v),v->inq=true; }
		if(T->dist==inf) break;
		int c=inf;
		for(e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for(e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d\n",Ans);
	scanf("\n");
}

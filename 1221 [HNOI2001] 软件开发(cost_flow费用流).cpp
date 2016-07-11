#include <cstdio>
#include <queue>
const int inf=0x7FFFFFFF,N=1005,M=6*N;
int n,a,b,f,fa,fb;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
struct node;
struct edge{
	node *pre,*ed; edge *next; int cap,cost;
} E[M<<1],*newE=E;
struct node{
	edge *son; int dist,flow; edge *fro; bool inq;
	node():son(NULL){}
};
inline void addedge(node *u,node *v,const int cap=inf,const int cost=0){
	*newE=(edge){u,v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){v,u,v->son,0,-cost},v->son=newE++;
}
//define graph
node S[2],*T=S+1,V[N][2];
int main(){
	scanf("%d%d%d%d%d%d",&n,&a,&b,&f,&fa,&fb); a++,b++;
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		addedge(S,V[i],x);
		addedge(V[i],V[i+1]);
		if(i+a<=n) addedge(V[i],V[i+a]+1,inf,fa);
		if(i+b<=n) addedge(V[i],V[i+b]+1,inf,fb);
		addedge(S,V[i]+1,inf,f);
		addedge(V[i]+1,T,x);
	}
	int Ans=0;
	int flo=0;
	for(;;){
		std::queue<node*> q; node *u,*v; edge *e;
		//clear
		for(int i=1;i<=n;i++) V[i][0].dist=V[i][1].dist=inf;
		S->dist=0;S->fro=NULL; T->dist=inf;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),u->inq=false)
			for(e=(u=q.front())->son;e;e=e->next)
				if(e->cap&&mini((v=e->ed)->dist,u->dist+e->cost))
					{ v->fro=e; if(!v->inq) q.push(v),v->inq=true; }
		if(T->dist==inf) break;
		int c=inf;
		for(e=T->fro;e;e=e->pre->fro)
			mini(c,e->cap);
		flo+=c;
		for(e=T->fro;e;e=e->pre->fro)
			e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d\n",Ans);
}

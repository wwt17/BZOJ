#include <cstdio>
#include <queue>
const int inf=(int)1e9+7,N=305,M=100+5005+N+N*2;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
int n;
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
node S[2],*T=S+1,V[N],s[2],*t=s+1;
int delta[N][2];

int main(){
	int Ans=0;
	scanf("%d",&n);
	addedge(t,s);
	addedge(s,V+1);
	for(int i=1;i<=n;i++){
		addedge(&V[i],t);
		int k; scanf("%d",&k);
		while(k--){
			int j,w; scanf("%d%d",&j,&w);
			Ans+=w;
			delta[i][0]++;
			delta[j][1]++;
			addedge(&V[i],&V[j],inf,w);
		}
	}
	for(int i=1;i<=n;i++){
		addedge(S,&V[i],delta[i][1]);
		addedge(&V[i],T,delta[i][0]);
	}
	for(;;){
		std::queue<node*> q; node *u,*v; edge *e;
		for(int i=1;i<=n;++i) V[i].dist=inf;
		s->dist=t->dist=inf;
		S->dist=0;S->fro=NULL; T->dist=inf;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),u->inq=false)
			for(e=(u=q.front())->son;e;e=e->next)
				if(e->cap&&mini((v=e->ed)->dist,u->dist+e->cost))
					{ v->fro=e; if(!v->inq&&v->dist<T->dist) q.push(v),v->inq=true; }
		if(T->dist==inf) break;
		int c=inf;
		for(e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		Ans+=T->dist*c;
		for(e=T->fro;e;e=e->pre->fro)
			e->cap-=c,E[(e-E)^1].cap+=c;
	}
	printf("%d\n",Ans);
}

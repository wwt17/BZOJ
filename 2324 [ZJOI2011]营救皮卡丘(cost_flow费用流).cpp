#include <cstdio>
#include <queue>
using namespace std;
const int N=151,inf=1000000000;
int n,m,k,dist[N][N],d[N][N];
inline void mini(int &a,const int b){
	if(b<a) a=b;
}
struct node;
struct edge{
	node *ed; int next; int cap,cost;
} E[(1+1+N*(N-1)/2+(N-1)*2)<<1];
int newE=2;
struct node{
	int son,pre; int dist; bool inq;
} mem[2],*S=mem,*T=mem+1,V[N][2];
inline void addedge(node *u,node *v,int cap,int cost){
	E[newE]=(edge){v,u->son,cap,cost},u->son=newE++;
	E[newE]=(edge){u,v->son, 0,-cost},v->son=newE++;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			dist[i][j]=i==j?0:inf;
	while(m--){
		static int a,b,l; scanf("%d%d%d",&a,&b,&l);
		mini(dist[a][b],l);
		mini(dist[b][a],l);
	}
	for(int d=0;d<=n;d++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++){
				if(j==d&&i<j)
					if(dist[i][j]<inf)
						addedge(V[i],V[j]+1,1,dist[i][j]);
				mini(dist[i][j],dist[i][d]+dist[d][j]);
			}
	addedge(S,V[0],k,0);
	for(int i=1;i<=n;i++){
		addedge(S,V[i],1,0);
		addedge(V[i]+1,T,1,0);
	}
	int ans=0;
	while(true){
		queue<node*> q; node *u,*v;
		S->pre=0;
		S->dist=0;
		T->dist=inf;
		for(int i=0;i<=n;i++) V[i][0].dist=V[i][1].dist=inf;
		for(q.push(S),S->inq=true;!q.empty();u->inq=false,q.pop())
			for(int e=(u=q.front())->son;e;e=E[e].next) if(E[e].cap)
				if(u->dist+E[e].cost<(v=E[e].ed)->dist){
					v->dist=u->dist+E[e].cost;
					v->pre=e;
					if(!v->inq&&v->dist<T->dist){
						q.push(v); v->inq=true;
					}
				}
		if(T->dist==inf) break;
		int flow=inf,cost=0;
		for(int e=T->pre;e;e=E[e^1].ed->pre){
			mini(flow,E[e].cap);
			cost+=E[e].cost;
		}
		ans+=flow*cost;
		for(int e=T->pre;e;e=E[e^1].ed->pre){
			E[e].cap-=flow;
			E[e^1].cap+=flow;
		}
	}
	printf("%d\n",ans);
}

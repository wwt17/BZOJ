#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x00010000
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node* ed; edge* next; int w;
	edge(node* _ed,edge* _next,int _w):ed(_ed),next(_next),w(_w){}
};
struct node{
	edge* son; bool inq,flag,f[101]; int dist;
	inline void addedge(node* ed,const int w){
		son=new edge(ed,son,w);
	}
} V[21];
int cost[101][101],f[101];
int main(){
	int n,m,K,e,d,P,a,b,w;
	scanf("%d%d%d%d",&n,&m,&K,&e);
	while(e--){
		scanf("%d%d%d",&a,&b,&w);
		V[a].addedge(V+b,w);
		V[b].addedge(V+a,w);
	}
	scanf("%d",&d);
	while(d--){
		scanf("%d%d%d",&P,&a,&b);
		memset(V[P].f+a,1,b-a+1);
	}
	std::queue<node*> q; node *u,*v;
	for(a=1;a<=n;++a){
		for(u=V+1;u<=V+m;++u) u->flag=false;
		for(b=a;b<=n;++b){
			for(u=V+1;u<=V+m;++u) u->flag|=u->f[b],u->dist=INF;
			for(V[1].dist=0,q.push(V+1),V[1].inq=true;!q.empty();u->inq=false,q.pop())
				for(edge* e=(u=q.front())->son;e;e=e->next)
					if(!(v=e->ed)->flag&&mini(v->dist,u->dist+e->w)&&!v->inq)
						q.push(v),v->inq=true;
			cost[a][b]=V[m].dist;
		}
	}
	for(b=1;b<=n;++b){
		f[b]=INF;
		for(a=0;a<b;++a)
			mini(f[b],f[a]+cost[a+1][b]*(b-a)+K);
	}
	printf("%d\n",f[n]-K);
}

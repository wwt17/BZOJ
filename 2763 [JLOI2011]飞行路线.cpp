#include <cstdio>
#include <queue>
#define INF 0x40000000
int N,M,K;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
struct node;
struct edge{
	node* ed; edge* next; int w;
	edge(node* _ed,edge* _next,int _w):
		ed(_ed),next(_next),w(_w){}
};
struct node{
	edge* son; int dist[11];
	void addedge(node* ed,int w){
		son=new edge(ed,son,w);
	}
} V[10000],*S,*T;
struct situ{
	node* v; int k;
	friend bool operator < (const situ &a,const situ &b){
		return a.v->dist[a.k]>b.v->dist[b.k];
	}
};
int main(){
	scanf("%u%u%u",&N,&M,&K);
	int u,v,w,i,k,s,t;
	scanf("%u%u",&s,&t); S=V+s; T=V+t;
	while(M--){
		scanf("%u%u%u",&u,&v,&w);
		V[u].addedge(V+v,w);
		V[v].addedge(V+u,w);
	}
	for(node* u=V;u<V+N;++u) for(k=K;k>=0;--k) u->dist[k]=INF;
	std::priority_queue<situ> h; situ x,y; edge *e;
	S->dist[K]=0; h.push((situ){S,K});
	while(!h.empty()){
		x=h.top();h.pop();
		if(y.k=x.k)
			for(e=x.v->son;e;e=e->next){
				y.v=e->ed;
				if(mini(y.v->dist[y.k],x.v->dist[x.k]+e->w))
					h.push(y);
				--y.k;
				if(mini(y.v->dist[y.k],x.v->dist[x.k]))
					h.push(y);
				++y.k;
			}
		else
			for(e=x.v->son;e;e=e->next){
				y.v=e->ed;
				if(mini(y.v->dist[y.k],x.v->dist[x.k]+e->w))
					h.push(y);
			}
	}
	int Ans=INF;
	for(k=K;k>=0;--k) mini(Ans,T->dist[k]);
	printf("%d\n",Ans);
}

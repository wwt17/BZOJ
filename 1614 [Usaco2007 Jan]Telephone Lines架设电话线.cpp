#include <cstdio>
#include <queue>
#define INF 0x40000000
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node *ed; edge *next; int len; bool w;
} E[20000],*newedge=E;
struct node{
	edge *son; int dist;
	inline void addedge(node *ed,int w){
		*newedge=(edge){ed,son,w,0};
		son=newedge++;
	}
} V[1001];
int N,P,K,i,u,v,w;
bool Check(const int bound){
	static std::deque<node*> q; node *u,*v; edge *e;
	for(e=E;e<newedge;++e) e->w=e->len>bound;
	for(u=V+1;u<=V+N;++u) u->dist=INF;
	q.push_back(V+1),V[1].dist=0;
	while(!q.empty()){
		u=q.front(),q.pop_front();
		for(e=u->son;e;e=e->next)
			if(mini((v=e->ed)->dist,u->dist+e->w))
				e->w?q.push_back(v):q.push_front(v);
	}
	return V[N].dist<=K;
}
int main(){
	scanf("%u%u%u",&N,&P,&K);
	while(P--){
		scanf("%u%u%u",&u,&v,&w);
		V[u].addedge(V+v,w);
		V[v].addedge(V+u,w);
	}
	int l=0,r=1000001,mid;
	while(l<r)
		if(Check(mid=(l+r)>>1))
			r=mid;
		else
			l=mid+1;
	printf("%d\n",l>1000000?-1:l);
}

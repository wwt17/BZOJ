#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=1501,M=5000,P=1000000007,inf=100000000;
int n,m;
struct node;
struct edge{
	node *ed; edge *next; int w,sum;
} E[M],*newE=E;
struct node{
	edge *son; int dist,cnt[2]; bool inq;
} V[N],*ord[N];
queue<node*> q;
inline bool cmp(const node* A,const node* B){
	return A->dist<B->dist;
}
int main(){
	scanf("%u%u",&n,&m);
	for(int i=0;i<m;i++){
		static int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		*newE=(edge){V+v,V[u].son,w,0},V[u].son=newE++;
	}
	for(int s=1;s<=n;s++){
		node *u,*v;
		for(int i=1;i<=n;i++) V[i].dist=inf;
		V[s].dist=0;
		q.push(V+s),V[s].inq=true;
		for(;!q.empty();u->inq=false,q.pop())
			for(edge *e=(u=q.front())->son;e;e=e->next)
				if(u->dist+e->w<(v=e->ed)->dist){
					v->dist=u->dist+e->w;
					if(!v->inq) q.push(v),v->inq=true;
				}
		for(int i=1;i<=n;i++) ord[i]=V+i,V[i].cnt[0]=0,V[i].cnt[1]=1;
		V[s].cnt[0]=1;
		sort(ord+1,ord+n+1,cmp);
		for(int i=1;i<=n;i++)
			for(edge* e=(u=ord[i])->son;e;e=e->next)
				if(u->dist+e->w==(v=e->ed)->dist)
					v->cnt[0]+=u->cnt[0];
		for(int i=n;i;i--)
			for(edge* e=(u=ord[i])->son;e;e=e->next)
				if(u->dist+e->w==(v=e->ed)->dist)
					u->cnt[1]+=v->cnt[1],
					e->sum=(e->sum+(long long)u->cnt[0]*v->cnt[1])%P;
	}
	for(edge* e=E;e<newE;e++) printf("%d\n",e->sum);
}

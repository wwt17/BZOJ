#include <cstdio>
#include <algorithm>
using namespace std;

template<class T>
T sqr(const T x){
	return x*x;
}

const int N=5005,M=1005;

int n,m;

const int intinf=(int)1e9+7;
const int sizeV=2+N+M,sizeE=M*5;
typedef int capType;
typedef int costType;
const capType capinf=intinf;
const costType costinf=intinf;
#define nonzero(x) bool(x)
struct node;
struct edge{
	node *ed;
	edge *next;
	capType cap;
	costType cost;
} E[sizeE<<1],*newE=E;
int distim;
struct node{
	edge *son,*fro;
	costType dist; int distim;
	bool inq;
} S[2],*T=S+1;
inline void addedge(node *u,node *v,const capType cap,const costType cost=0){
	*newE=(edge){v,u->son,cap, cost},u->son=newE++;
	*newE=(edge){u,v->son,  0,-cost},v->son=newE++;
}
#define oppo(e) (E+(((e)-E)^1))
pair<capType,costType> costflow(){
	pair<capType,costType> ret(0,0);
	while(true){
		static node *q[sizeV];
		int head=0,tail=0;
		distim++;
		S->distim=distim;
		S->dist=0;
		q[tail++]=S;
		S->inq=true;
		while(head!=tail){
			node *u=q[head]; if(++head==sizeV) head=0; u->inq=false;
			for(edge *e=u->son;e;e=e->next) if(e->cap){
				node *v=e->ed;
				if(v->distim!=distim||u->dist+e->cost<v->dist){
					v->distim=distim;
					v->dist=u->dist+e->cost;
					v->fro=e;
					if(!v->inq){
						q[tail]=v; if(++tail==sizeV) tail=0; v->inq=true;
					}
				}
			}
		}
		if(T->distim!=distim) break;
		capType cap=capinf;
		for(node *u=T;u!=S;u=oppo(u->fro)->ed)
			cap=min(cap,u->fro->cap);
		ret.first+=cap;
		for(node *u=T;u!=S;u=oppo(u->fro)->ed){
			ret.second+=cap*u->fro->cost;
			u->fro->cap-=cap;
			oppo(u->fro)->cap+=cap;
		}
	}
	return ret;
}
#define inf intinf

node a[N],b[M];

int ans;

int win[N],lose[N],C[N],D[N],deg[N];

edge *e[M];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&win[i],&lose[i],&C[i],&D[i]);
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d",&x,&y);
		++deg[x];
		++deg[y];
		addedge(&a[x],&b[i],1,0);
		addedge(&a[y],&b[i],1,0);
		addedge(&b[i],T,1,0);
	}
	for(int i=1;i<=n;i++){
		ans+=C[i]*sqr(win[i])+D[i]*sqr(lose[i]+deg[i]);
		for(int j=1;j<=deg[i];j++)
			addedge(S,&a[i],1,-(C[i]*sqr(win[i]+j-1)+D[i]*sqr(lose[i]+deg[i]-(j-1)))+(C[i]*sqr(win[i]+j)+D[i]*sqr(lose[i]+deg[i]-j)));
	}
	printf("%d\n",ans+costflow().second);
}

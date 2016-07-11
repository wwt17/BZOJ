#include <cstdio>
#include <algorithm>
using namespace std;

const int N=105;

int n;

const int intinf=(int)1e9+7;
const int sizeV=2+N+N*N,sizeE=N*N*5;
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

int g[N][N];

node a[N],b[N][N];

edge *e[N][N];

inline int calc(int n){
	return n*(n-1)/2;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&g[i][j]);
			if(i<j){
				addedge(&b[i][j],T,1,0);
				e[i][j]=newE;
				if(g[i][j]!=0) addedge(&a[i],&b[i][j],1,0);
				if(g[i][j]!=1) addedge(&a[j],&b[i][j],1,0);
			}
		}
	int ans=0;
	for(int i=1;i<=n;i++){
		int last=calc(0)+calc(n-1);
		ans+=last;
		for(int j=1;j<=n-1;j++){
			int now=calc(j)+calc(n-1-j);
			addedge(S,&a[i],1,now-last);
			last=now;
		}
	}
	ans=n*(n-1)*(n-2)/6-(ans+costflow().second)/2;
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++) if(g[i][j]==2){
			g[j][i]=e[i][j]->cap;
			g[i][j]=1-g[j][i];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) printf("%d%c",g[i][j]," \n"[j==n]);
}

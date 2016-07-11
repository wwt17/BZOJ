#include <cstdio>
#include <queue>
using namespace std;
const int N=45,M=105,P=805,inf=(int)1e9;
int n,m,sp,t[N][M],cnt[M];
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap,cost;
} E[N+N*M*P+M*P<<1],*newE=E;
struct node{
	edge *son,*pre;
	int dist;
	bool inq;
} S[2],*T=S+1,dish[N],chef[M][P];
void addedge(node *u,node *v,int cap,int cost){
	*newE=(edge){v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){u,v->son, 0,-cost},v->son=newE++;
}
void setdist(){
	for(int i=1;i<=n;i++) dish[i].dist=inf;
	for(int j=1;j<=m;j++)
		for(int k=1;k<=cnt[j];k++)
			chef[j][k].dist=inf;
	S->dist=T->dist=inf;
}
void spfa(){
	static queue<node*> q;
	setdist();
	S->dist=0;
	q.push(S);
	S->inq=1;
	while(!q.empty()){
		node *u=q.front(); q.pop(); u->inq=0;
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(u->dist+e->cost<v->dist){
				v->dist=u->dist+e->cost;
				v->pre=e;
				if(!v->inq){
					v->inq=1;
					q.push(v);
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	// addedge(S,dish[i],p[i],0)
	// addedge(dish[i],chef[j][k],1,k*t[i][j])
	// addedge(chef[j][k],T,1,0)
	for(int i=1;i<=n;i++){
		int p; scanf("%d",&p); sp+=p;
		addedge(S,&dish[i],p,0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			scanf("%d",&t[i][j]);
	}
	for(int j=1;j<=m;j++){
		cnt[j]=1;
		for(int i=1;i<=n;i++)
			addedge(&dish[i],&chef[j][1],1,t[i][j]);
		addedge(&chef[j][1],T,1,0);
	}
	int ans=0;
	while(sp--){
		spfa();
		ans+=T->dist;
		for(node *u=T;u!=S;u=E[u->pre-E^1].ed){
			u->pre->cap--;
			E[u->pre-E^1].cap++;
		}
		for(int j=1;j<=m;j++) if(!chef[j][cnt[j]].son->cap){
			cnt[j]++;
			for(int i=1;i<=n;i++)
				addedge(&dish[i],&chef[j][cnt[j]],1,cnt[j]*t[i][j]);
			addedge(&chef[j][cnt[j]],T,1,0);
		}
	}
	printf("%d\n",ans);
}

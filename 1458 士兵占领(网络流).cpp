#include <cstdio>
#include <queue>
using namespace std;
const int M=101,N=101;
int m,n,k;
inline int min(const int a,const int b){
	return a<b?a:b;
}
struct node;
struct edge{
	node *ed; edge *next; int cap;
} E[(N*M+N+M)*2],*newE=E;
struct node{
	edge *son; int depth;
} R[M],C[N],*S=R,*T=C;
bool build(){
	for(int i=1;i<=m;i++) R[i].depth=0;
	for(int j=1;j<=n;j++) C[j].depth=0;
	T->depth=0;
	queue<node*> q;
	q.push(S);
	S->depth=1;
	for(node *u,*v;!q.empty();q.pop())
		for(edge *e=(u=q.front())->son;e;e=e->next)
			if(e->cap&&!(v=e->ed)->depth){
				v->depth=u->depth+1;
				q.push(v);
				if(v==T) return true;
			}
	return false;
}
int flow(node *u,int F){
	if(u==T) return F;
	node *v; int rest=F,f;
	for(edge *e=u->son;e&&rest;e=e->next)
		if(e->cap&&(v=e->ed)->depth==u->depth+1&&(f=flow(v,min(rest,e->cap))))
			rest-=f,e->cap-=f,E[(e-E)^1].cap+=f;
	if(rest==F) u->depth=0;
	return F-rest;
}
void addedge(node *u,node *v,int cap1,int cap2){
	*newE=(edge){v,u->son,cap1},u->son=newE++;
	*newE=(edge){u,v->son,cap2},v->son=newE++;
}
int x[M],y[N];
bool f[M][N];
int main(){
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=m;i++) scanf("%d",&x[i]),x[i]=n-x[i];
	for(int j=1;j<=n;j++) scanf("%d",&y[j]),y[j]=m-y[j];
	for(int i=0;i<k;i++){
		int X,Y; scanf("%d%d",&X,&Y);
		f[X][Y]=true;
		if(!x[X]--||!y[Y]--){
			puts("ke lian de BG!");
			return 0;
		}
	}
	for(int i=1;i<=m;i++) addedge(S,R+i,x[i],0);
	for(int j=1;j<=n;j++) addedge(C+j,T,y[j],0);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(!f[i][j])
				addedge(R+i,C+j,1,0);
	int Ans=n*m-k,Flow;
	while(build())
		while(Flow=flow(S,m*n))
			Ans-=Flow;
	printf("%d\n",Ans);
}

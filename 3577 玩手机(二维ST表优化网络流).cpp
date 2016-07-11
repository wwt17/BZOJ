#include <cstdio>
#include <algorithm>
using namespace std;
const int N=64,logN=6,C=10005,inf=(int)1e9+7,sizeV=2+C+C+logN*N*N*2,sizeE=(C+C)*4+logN*N*N*4*2+N*N;
int n,m,a,b;
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[sizeE<<1],*newE=E;
struct node{
	edge *son;
	int lab,labtim;
} S[2],*T=S+1;
void addedge(node *u,node *v,int cap0=inf,int cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}
int labtime=0;
bool layer(){
	labtime++;
	static node *q[sizeV];
	int head=0,tail=0;
	q[tail++]=S;
	S->labtim=labtime;
	S->lab=0;
	while(head!=tail){
		node *u=q[head++];
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(v->labtim==labtime) continue;
			v->labtim=labtime;
			v->lab=u->lab+1;
			if(v==T)
				return true;
			q[tail++]=v;
		}
	}
	return false;
}
int flow(node *u,int F){
	if(u==T) return F;
	int left=F;
	for(edge *e=u->son;e&&left;e=e->next) if(e->cap){
		node *v=e->ed;
		if(v->labtim!=labtime||v->lab!=u->lab+1) continue;
		int f=flow(v,min(left,e->cap));
		e->cap-=f;
		E[e-E^1].cap+=f;
		left-=f;
	}
	if(left==F) u->labtim=0;
	return F-left;
}
int network_flow(){
	int ans=0,f;
	while(layer())
		while(f=flow(S,inf))
			ans+=f;
	return ans;
}
node A[C],B[C],ST[logN][N][N][2];
int base[N];
int main(){
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=2;i<=n;i++) base[i]=base[i>>1]+1;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			int x; scanf("%d",&x);
			addedge(&ST[0][i][j][0],&ST[0][i][j][1],x);
		}
	for(int i=0;i<a;i++){
		int w,x1,y1,x2,y2; scanf("%d%d%d%d%d",&w,&x1,&y1,&x2,&y2); x1--; y1--;
		addedge(S,&A[i],w);
		int b=base[x2-x1];
		addedge(&A[i],&ST[b][x1][y1][0]);
		addedge(&A[i],&ST[b][x2-(1<<b)][y1][0]);
		addedge(&A[i],&ST[b][x1][y2-(1<<b)][0]);
		addedge(&A[i],&ST[b][x2-(1<<b)][y2-(1<<b)][0]);
	}
	for(int i=0;i<b;i++){
		int w,x1,y1,x2,y2; scanf("%d%d%d%d%d",&w,&x1,&y1,&x2,&y2); x1--; y1--;
		addedge(&B[i],T,w);
		int b=base[x2-x1];
		addedge(&ST[b][x1][y1][1],&B[i]);
		addedge(&ST[b][x2-(1<<b)][y1][1],&B[i]);
		addedge(&ST[b][x1][y2-(1<<b)][1],&B[i]);
		addedge(&ST[b][x2-(1<<b)][y2-(1<<b)][1],&B[i]);
	}
	for(int b=1;b<=base[n];b++)
		for(int x=0;x+(1<<b)<=n;x++)
			for(int y=0;y+(1<<b)<=n;y++){
				addedge(&ST[b][x][y][0],&ST[b-1][x][y][0]);
				addedge(&ST[b][x][y][0],&ST[b-1][x+(1<<b-1)][y][0]);
				addedge(&ST[b][x][y][0],&ST[b-1][x][y+(1<<b-1)][0]);
				addedge(&ST[b][x][y][0],&ST[b-1][x+(1<<b-1)][y+(1<<b-1)][0]);
				addedge(&ST[b-1][x][y][1],&ST[b][x][y][1]);
				addedge(&ST[b-1][x+(1<<b-1)][y][1],&ST[b][x][y][1]);
				addedge(&ST[b-1][x][y+(1<<b-1)][1],&ST[b][x][y][1]);
				addedge(&ST[b-1][x+(1<<b-1)][y+(1<<b-1)][1],&ST[b][x][y][1]);
			}
	printf("%d\n",network_flow());
}

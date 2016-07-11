#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=100,M=100,inf=2100000000;
int n,m,a[N][M],b[N][M],c[N][M],d[N][M];
struct node;
struct edge{
	node *ed; int next; int cap;
} E[N*N*4<<1]; int newE=2;
struct node{
	int son; int depth;
} S[2],*T=S+1,V[N][N];
inline void addedge(node *u,node *v,int c1,int c2=0){
	E[newE]=(edge){v,u->son,c1},u->son=newE++;
	E[newE]=(edge){u,v->son,c2},v->son=newE++;
}
bool build(){
	queue<node*> q;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			V[i][j].depth=0;
	T->depth=0;
	S->depth=1;
	q.push(S);
	while(!q.empty()){
		node *u=q.front(); q.pop();
		for(int e=u->son;e;e=E[e].next) if(E[e].cap){
			node *v=E[e].ed;
			if(!v->depth){
				v->depth=u->depth+1;
				if(v==T) return true;
				q.push(v);
			}
		}
	}
	return false;
}
int flow(node *u,int F){
	if(u==T) return F;
	int left=F;
	node *v;
	for(int e=u->son;e&&left;e=E[e].next) if(E[e].cap&&(v=E[e].ed)->depth==u->depth+1){
		int f=flow(v,min(left,E[e].cap));
		left-=f;
		E[e].cap-=f;
		E[e^1].cap+=f;
	}
	if(!(F-=left)) u->depth=0;
	return F;
}
int main(){
	scanf("%d%d",&n,&m);
	int ans=0,x;
	#define read() scanf("%d",&x),ans+=x*2
	#define read2() scanf("%d",&x),ans+=x*=2
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			read2();
			a[i][j]=x;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			read2();
			b[i][j]=x;
		}
	for(int i=0;i<n-1;i++)
		for(int j=0;j<m;j++){
			read();
			a[i][j]+=x;
			a[i+1][j]+=x;
			c[i][j]=x;
		}
	for(int i=0;i<n-1;i++)
		for(int j=0;j<m;j++){
			read();
			b[i][j]+=x;
			b[i+1][j]+=x;
			c[i][j]+=x;
			addedge(&V[i][j],&V[i+1][j],c[i][j],c[i][j]);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m-1;j++){
			read();
			a[i][j]+=x;
			a[i][j+1]+=x;
			c[i][j]=x;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m-1;j++){
			read();
			b[i][j]+=x;
			b[i][j+1]+=x;
			c[i][j]+=x;
			addedge(&V[i][j],&V[i][j+1],c[i][j],c[i][j]);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			addedge(S,&V[i][j],a[i][j]);
			addedge(&V[i][j],T,b[i][j]);
		}
	while(build()){
		int f;
		while(f=flow(S,inf))
			ans-=f;
	}
	printf("%d\n",ans/2);
}

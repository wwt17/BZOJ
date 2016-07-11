#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=100,M=100,inf=2100000000;
int n,m,c[N][M];
struct node;
struct edge{
	node *ed; int next; int cap;
} E[N*N*4<<1]; int newE=2;
struct node{
	int son; int depth;
} S[2],*T=S+1,V[N][N];
inline void addedge(node *u,node *v,int c){
	E[newE]=(edge){v,u->son,c},u->son=newE++;
	E[newE]=(edge){u,v->son,0},v->son=newE++;
}
inline void addedge2(node *u,node *v,int c){
	E[newE]=(edge){v,u->son,c},u->son=newE++;
	E[newE]=(edge){u,v->son,c},v->son=newE++;
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
	int ans=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			static int a; scanf("%d",&a);
			if((i^j)&1)
				addedge(S,&V[i][j],a);
			else
				addedge(&V[i][j],T,a);
			ans+=a;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			static int b; scanf("%d",&b);
			if((i^j)&1)
				addedge(&V[i][j],T,b);
			else
				addedge(S,&V[i][j],b);
			ans+=b;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			scanf("%d",&c[i][j]);
			if(i) addedge2(&V[i-1][j],&V[i][j],c[i-1][j]+c[i][j]),ans+=c[i][j]+c[i-1][j];
			if(j) addedge2(&V[i][j-1],&V[i][j],c[i][j-1]+c[i][j]),ans+=c[i][j]+c[i][j-1];
		}
	while(build()){
		int f;
		while(f=flow(S,inf))
			ans-=f;
	}
	printf("%d\n",ans);
}

#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=40,inf=2100000000;
int n;
struct node;
struct edge{
	node *ed; int next; int cap;
} E[N*N*N*5<<1]; int newE=2;
struct node{
	int son; int depth;
} S[2],*T=S+1,V[N][N][N];
inline void addedge(node *u,node *v,int c){
	E[newE]=(edge){v,u->son,c},u->son=newE++;
	E[newE]=(edge){u,v->son,0},v->son=newE++;
}
bool build(){
	queue<node*> q;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++)
				V[i][j][k].depth=0;
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
	scanf("%d",&n);
	int tot=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++){
				int cnt=0;
				if(i){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i-1][j][k],2); cnt++; }
				if(j){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i][j-1][k],2); cnt++; }
				if(k){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i][j][k-1],2); cnt++; }
				if(i<n-1){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i+1][j][k],2); cnt++; }
				if(j<n-1){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i][j+1][k],2); cnt++; }
				if(k<n-1){ if((i^j^k)&1) addedge(&V[i][j][k],&V[i][j][k+1],2); cnt++; }
				tot+=cnt;
				rep:
				switch(getchar()){
					case 'P':
						if((i^j^k)&1)
							addedge(S,&V[i][j][k],inf);
						else
							addedge(&V[i][j][k],T,inf);
						break;
					case 'N':
						if((i^j^k)&1)
							addedge(&V[i][j][k],T,inf);
						else
							addedge(S,&V[i][j][k],inf);
						break;
					case '?':
						break;
					default:
						goto rep;
				}
						if((i^j^k)&1)
							addedge(S,&V[i][j][k],cnt);
						else
							addedge(&V[i][j][k],T,cnt);
			}
	int ans=tot;
	while(build()){
		int f;
		while(f=flow(S,inf))
			ans-=f;
	}
	printf("%d\n",ans);
}

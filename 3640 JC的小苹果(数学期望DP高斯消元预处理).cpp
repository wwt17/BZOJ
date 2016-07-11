#include <cstdio>

const int N=155,M=5005,H=10005;

int n,hp,m;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	int a,cnt;
	double f[H];
} V[N];

double mat[N][N];

int main(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	scanf("%d%d%d",&n,&m,&hp);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].a);
	for(int i=0;i<m;i++){
		static int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++; V[x].cnt++;
		if(x==y) continue;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++; V[y].cnt++;
	}
	for(int i=1;i<n;i++) if(!V[i].a){
		mat[i][i]=V[i].cnt;
		for(edge *e=V[i].son;e;e=e->next)
			mat[i][e->ed-V]-=1;
	}
	for(int i=1;i<n;i++) if(!V[i].a){
		for(int k=1;k<=n;k++) if(k!=i) mat[i][k]/=mat[i][i];
		mat[i][i]=1;
		for(int j=1;j<=n;j++) if(!V[j].a&&j!=i){
			for(int k=1;k<=n;k++) if(k!=i)
				mat[j][k]-=mat[j][i]*mat[i][k];
			mat[j][i]=0;
		}
	}
	for(int h=1;h<=hp;h++){
		for(int i=1;i<n;i++) if(h>V[i].a&&V[i].a){
			for(edge *e=V[i].son;e;e=e->next)
				V[i].f[h]+=V[e->ed-V].f[h-V[i].a];
			V[i].f[h]/=V[i].cnt;
		}
		V[n].f[h]=1;
		for(int i=1;i<n;i++) if(!V[i].a){
			for(int j=1;j<=n;j++) if(j!=i)
				V[i].f[h]-=V[j].f[h]*mat[i][j];
		}
	}
	printf("%.8lf\n",V[1].f[hp]);
	scanf("\n");
}

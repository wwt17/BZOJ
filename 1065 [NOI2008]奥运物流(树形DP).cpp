#include <cstdio>
#include <algorithm>
using namespace std;
typedef double db;
const db inf=1./0;
const int N=65,M=N;
int n,m,cir;
db power[N];
struct node{
	node *son,*next,*pa;
	db c,f[M][N];
	void work();
} V[N];
void node::work(){
	for(int i=0;i<=m;i++)
		for(int j=0;j<=n;j++)
			f[i][j]=c*power[j];
	for(node *v=son;v;v=v->next){
		v->work();
		for(int i=m;i>=0;i--)
			for(int j=0;j<=n;j++){
				db now=-inf;
				for(int k=0;k<=i;k++)
					now=max(now,f[i-k][j]+v->f[k][j+1]);
				f[i][j]=now;
			}
	}
	if(this==V[1].pa)
		for(int i=0;i<=m;i++)
			for(int j=0;j<=n+1;j++)
				if(j!=cir-1) f[i][j]=-inf;
	for(int i=1;i<=m;i++)
		for(int j=2;j<=n+1;j++)
			f[i][j]=max(f[i][j],f[i-1][1]);
}
int main(){
	scanf("%d%d%lf",&n,&m,&power[1]);
	power[0]=1;
	for(int i=2;i<=n;i++) power[i]=power[i-1]*power[1];
	for(int i=1;i<=n;i++){
		int s; scanf("%d",&s);
		V[i].pa=V+s;
		if(i!=1){
			V[i].next=V[s].son;
			V[s].son=V+i;
		}
	}
	for(int i=1;i<=n;i++) scanf("%lf",&V[i].c);
	db ans=0;
	int len=1;
	for(node *u=V[1].pa;u!=V+1;u=u->pa) len++;
	for(cir=2;cir<=len;cir++){
		V[1].work();
		ans=max(ans,V[1].f[m][0]/(1-power[cir]));
	}
	printf("%.2lf\n",ans);
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef double db;

const int N=10005,M=1005;
const int inf=1e9,eps=0;

int n/*variables*/,m/*constraints*/;

int a[M][N],c[N+M];
int indn[N],indm[M];

void pivot(int d,int e){ //d: basic e: non-basic
	if(a[d][e]==-1){
		for(int i=0;i<=n;i++) if(i!=e) a[d][i]=-a[d][i];
		a[d][e]=-1;
	}
	for(int i=0;i<=m;i++) if(i!=d&&a[i][e]){
		for(int j=0;j<=n;j++) if(j!=e) a[i][j]-=a[i][e]*a[d][j]; a[i][e]=-a[i][e]*a[d][e];
	}
	swap(indm[d],indn[e]);
}

int simplex(){
	while(true){
		int e=0;
		for(int i=1;i<=n;i++) if(a[0][i]>eps&&indn[i]<indn[e]) e=i;
		if(!e) return -a[0][0];
		int best=inf;
		int d=0;
		for(int i=1;i<=m;i++) if(a[i][e]>eps&&(a[i][0]<best||a[i][0]==best&&indm[i]<indm[d])){
			best=a[i][0];
			d=i;
		}
		if(!d) return inf;
		pivot(d,e);
	}
}

bool init(){
	indn[0]=indm[0]=n+m+10;
	int best=inf;
	int d=0;
	for(int i=1;i<=m;i++) if(a[i][0]<best){
		best=a[i][0];
		d=i;
	}
	if(best>=eps) return 1;
	indn[++n]=0;
	for(int i=0;i<=m;i++) a[i][n]=-1;
	pivot(d,n);
	a[0][0]=0;
	int tmp=simplex();
	if(tmp<-eps) return 0;
	for(int i=1;i<=m;i++) if(!indm[i]){
		pivot(i,1);
		break;
	}
	for(int i=1;i<=n;i++) if(!indn[i]){
		n--;
		for(int k=i;k<=n;k++){
			indn[k]=indn[k+1];
			for(int j=0;j<=m;j++)
				a[j][k]=a[j][k+1];
		}
		break;
	}
	for(int i=0;i<=m;i++) a[0][i]=0;
	return 1;
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) scanf("%d",&a[i][0]),a[i][0]*=-1;
	for(int i=1;i<=n;i++){
		int s,t;
		scanf("%d%d%d",&s,&t,&c[i]);
		c[i]*=-1;
		for(int j=s;j<=t;j++) a[j][i]=-1;
	}
	for(int i=1;i<=n;i++) indn[i]=i;
	for(int i=1;i<=m;i++) indm[i]=n+i;
	if(!init()){
		puts("No Solution!");
		return 0;
	}
	for(int j=n+1;j<=n+m;j++) c[j]=0;
	for(int i=1;i<=n;i++) a[0][i]=c[indn[i]];
	for(int i=1;i<=m;i++)
		for(int j=0;j<=n;j++) a[0][j]-=c[indm[i]]*a[i][j];
	printf("%d\n",int(-simplex()));
}

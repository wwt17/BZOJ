#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef double db;

const int N=1005,M=10005;
const int inf=1e9,eps=0;

int n/*variables*/,m/*constraints*/;

int a[M][N];
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

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[0][i]);
	for(int i=1;i<=m;i++){
		int s,t;
		scanf("%d%d%d",&s,&t,&a[i][0]);
		for(int j=s;j<=t;j++) a[i][j]=1;
	}
	indn[0]=indm[0]=n+m+1;
	for(int i=1;i<=n;i++) indn[i]=i;
	for(int i=1;i<=m;i++) indm[i]=n+i;
	printf("%d\n",simplex());
}

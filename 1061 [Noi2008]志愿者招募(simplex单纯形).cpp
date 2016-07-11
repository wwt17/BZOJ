#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;

const int N=1005,M=10005;

const db inf=1e30,eps=1e-7;

int n,m;

db a[M][N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		a[0][i]=x;
	}
	for(int i=1;i<=m;i++){
		int s,t,c; scanf("%d%d%d",&s,&t,&c); a[i][0]=c;
		for(int j=s;j<=t;j++) a[i][j]=1;
	}
	for(;;){
		int e;
		for(e=1;e<=n;e++) if(a[0][e]>eps) break;
		if(e>n){
			printf("%lld\n",(long long)round(-a[0][0]));
			break;
		}
		int d=0;
		db best=inf;
		for(int i=1;i<=m;i++) if(a[i][e]>eps&&a[i][0]/a[i][e]<best){
			best=a[i][0]/a[i][e];
			d=i;
		}
		if(!d){
			puts("no solution");
			break;
		}
		for(int j=0;j<=n;j++) if(j!=e) a[d][j]/=a[d][e]; a[d][e]=1/a[d][e];
		for(int i=0;i<=m;i++) if(i!=d){
			for(int j=0;j<=n;j++) if(j!=e) a[i][j]-=a[i][e]*a[d][j]; a[i][e]=-a[i][e]*a[d][e];
		}
	}
}

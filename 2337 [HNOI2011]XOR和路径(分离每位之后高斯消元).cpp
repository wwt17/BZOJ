#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
const int N=105,M=10005,W=30;
int n,m,b[N][N];
db a[N][N];
int q[M][3];
void add(int u,int v,int z){
	if(u==n) return;
	a[u][u]+=1;
	a[u][v]+=z?1:-1;
	a[u][0]+=z;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
		scanf("%d%d%d",&q[i][0],&q[i][1],&q[i][2]);
	db ans=0;
	for(int c=0;c<W;c++){
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n;j++)
				a[i][j]=0;
		for(int i=0;i<m;i++){
			add(q[i][0],q[i][1],q[i][2]>>c&1);
			if(q[i][0]!=q[i][1])
			add(q[i][1],q[i][0],q[i][2]>>c&1);
		}
		a[n][n]=1;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++) if(fabs(a[j][i])>1e-8){
				swap(a[i][0],a[j][0]);
				for(int k=i;k<=n;k++) swap(a[i][k],a[j][k]);
				break;
			}
			a[i][0]/=a[i][i];
			for(int k=n;k>=i;k--) a[i][k]/=a[i][i];
			for(int j=1;j<=n;j++) if(j!=i){
				a[j][0]-=a[i][0]*a[j][i];
				for(int k=n;k>=i;k--) a[j][k]-=a[i][k]*a[j][i];
			}
		}
		ans+=a[1][0]*(1<<c);
	}
	printf("%.3lf\n",ans);
}

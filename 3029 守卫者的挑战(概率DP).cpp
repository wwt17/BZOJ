#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef double db;
const int N=205;
int n,m,l,k,F;
db p[N];
int a[N];
db f[N][N*2],g[N][N*2];
int main(){
	scanf("%d%d%d",&n,&l,&k);
	for(int i=1;i<=n;i++) scanf("%lf",&p[i]),p[i]/=100;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0][min(k,n)+n]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)
			for(int k=-n;k<=n;k++){
				g[j][k+n]+=(1-p[i])*f[j][k+n];
				if(k+a[i]>=-n)
					g[j+1][min(k+a[i],n)+n]+=p[i]*f[j][k+n];
			}
		for(int j=0;j<=i;j++){
			memcpy(f[j],g[j],sizeof(db)*(n*2+1));
			memset(g[j],0,sizeof(db)*(n*2+1));
		}
	}
	db ans=0;
	for(int j=l;j<=n;j++)
		for(int k=0;k<=n;k++)
			ans+=f[j][k+n];
	printf("%.6lf\n",ans);
}

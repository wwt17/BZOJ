#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;

const db eps=1e-8;

const int N=305;

int n;

db a[N][N*2];

bool g[N][N];

bool gauss(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) if(fabs(a[j][i])>eps){
			for(int k=i;k<=n*2;k++) swap(a[i][k],a[j][k]);
			break;
		}
		if(fabs(a[i][i])<eps) return false;
		for(int k=n*2;k>=i;k--) a[i][k]/=a[i][i];
		for(int j=1;j<=n;j++) if(j!=i){
			for(int k=n*2;k>=i;k--) a[j][k]-=a[j][i]*a[i][k];
		}
	}
	return true;
}

int tim,vis[N];
int mat[N];

bool extend(int u){
	for(int v=1;v<=n;v++) if(vis[v]!=tim&&g[u][v]){
		vis[v]=tim;
		if(mat[v]==0||extend(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}

int from;
bool extend2(int u){
	for(int v=1;v<=n;v++) if(vis[v]!=tim&&g[u][v]){
		vis[v]=tim;
		if(mat[v]==from||mat[v]>from&&extend2(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&a[j][i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&a[j][i+n]);
	if(!gauss()){
		puts("NIE");
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			g[i][j]=fabs(a[i][j+n])>eps;
	for(int i=1;i<=n;i++){
		++tim;
		if(!extend(i)){
			puts("NIE");
			return 0;
		}
	}
	puts("TAK");
	for(int i=1;i<=n;i++){
		++tim;
		from=i;
		extend2(i);
		for(int j=1;j<=n;j++) if(mat[j]==i){
			printf("%d\n",j);
		}
	}
}

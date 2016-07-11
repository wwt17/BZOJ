#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1005;

int n,m,ans,a[N][N],f[N][N];

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
		for(int i=0;i<=n+1;i++) for(int j=m+1;j>=0;j--)
			f[i][j]=i==0||j==m+1?0:max(max(f[i-1][j],f[i][j+1]),(i==n+1||j==0?0:a[i][j])+f[i-1][j+1]);
		printf("%d\n",f[n+1][0]);
	}
}

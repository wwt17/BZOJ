/*
DP
f[i][j]表示做了前i个数，以第i个数结尾的子序列长度为j，另一个序列结尾最小的数。
O(T*N^2) 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=2015,inf=(int)1e8;

int n,m,a[N],f[N][N];

bool work(){
	scanf("%d",&n);
	m=n/2;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0][0]=a[0]=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i&&j<=m;j++)
			f[i][j]=min(a[i-1]<a[i]?f[i-1][j-1]:inf,i-j>0&&i-j<=i-1&&i-j<=m&&f[i-1][i-j]<a[i]?a[i-1]:inf);
	return f[n][m]<inf;
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		puts(work()?"Yes!":"No!");
}

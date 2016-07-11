// f[k][i][j]=sigma{ f[k-1][i-I][j-J]*C(i,I)*C(j,J)*g[t[i]][I][J] }
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=32,M=32,P=1000000009;
int n,m,c,t[11],f[11][N][M],g[N][M],C[N*M][N*M];
int main(){
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=c;i++) scanf("%d",&t[i]);
	for(int i=0;i<=n*m;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[0][i][j]=1;
	for(int k=1;k<=c;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++){
				g[i][j]=C[i*j][t[k]];
				for(int I=0;I<=i;I++)
					for(int J=0;J<=j;J++){
						if(I!=i||J!=j) g[i][j]=(g[i][j]-(long long)g[I][J]*C[i][I]%P*C[j][J])%P;
						f[k][i][j]=(f[k][i][j]+(long long)f[k-1][i-I][j-J]*C[i][I]%P*C[j][J]%P*g[I][J])%P;
					}
			}
	printf("%d\n",(f[c][n][m]+P)%P);
}

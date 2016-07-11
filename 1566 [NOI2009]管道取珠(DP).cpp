#include <cstdio>
const int N=505,mo=1024523;
int n,m;
char a[N],b[N];
int F,f[2][N][N];
int main(){
	scanf("%d%d%s%s",&n,&m,a+1,b+1);
	for(int i=0;i<=n;F^=1,i++)
		for(int j=0;j<=m;j++)
			for(int ii=0;ii<=n;ii++){
				int jj=i+j-ii;
				if(jj<0) break;
				if(jj>m) continue;
				if(!(i||j||ii||jj)){
					f[!F][j][ii]=1;
					continue;
				}
				f[!F][j][ii]=(
					 (i&&ii&&a[i]==a[ii]?f[F][j][ii-1]:0)
					+(i&&jj&&a[i]==b[jj]?f[F][j][ii]:0)
					+(j&&ii&&b[j]==a[ii]?f[!F][j-1][ii-1]:0)
					+(j&&jj&&b[j]==b[jj]?f[!F][j-1][ii]:0)
					)%mo;
			}
	printf("%d\n",f[F][m][n]);
}

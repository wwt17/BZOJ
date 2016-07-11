#include <cstdio>
#define N 51
int n,a[N][N],b[N][N],i,j,x,y,f[2][N][N][N],Ans; bool I;
inline int min(const int a,const int b){return a<b?a:b;}
#define min(a,b,c) min(min(a,b),c)
inline void maxi(int &a,const int b){if(a<b)a=b;}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;++i) for(j=1;j<=n;++j)	scanf("%d",&a[i][j]);
	for(i=1;i<=n;++i) for(j=1;j<=n;++j)	scanf("%d",&b[i][j]);
	for(i=I=1;i<=n;++i,I^=1) for(j=1;j<=n;++j)	for(x=1;x<=n;++x) for(y=1;y<=n;++y)
		maxi(Ans,f[I][j][x][y]=(a[i][j]==b[x][y]?min(f[!I][j][x-1][y],f[I][j-1][x][y-1],f[!I][j-1][x-1][y-1])+1:0));
	printf("%d\n",Ans);
}

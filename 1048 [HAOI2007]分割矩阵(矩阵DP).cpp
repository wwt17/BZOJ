#include <cstdio>
#include <cmath>
typedef double db;
const int N=11,M=N,O=N;
const db inf=1./0;
inline db sqr(const db x){
	return x*x;
}
inline db fix(const db x){
	return x?x:inf;
}
int n,m,o;
db ave,s[N][M],f[N][N][M][M][O];
int main(){
	scanf("%d%d%d",&n,&m,&o);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&s[i][j]),
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	ave=s[n][m]/o;
	for(int k=1;k<=o;k++)
	for(int x0=0;x0<n;x0++)
	for(int x1=x0+1;x1<=n;x1++)
	for(int y0=0;y0<m;y0++)
	for(int y1=y0+1;y1<=m;y1++)
		if(k==1)
			f[x0][x1][y0][y1][1]=sqr(s[x0][y0]-s[x1][y0]-s[x0][y1]+s[x1][y1]-ave)+1;
		else{
			db res=inf;
			for(int kk=1;kk<k;kk++){
				for(int x=x0+1;x<x1;x++){
					db now=fix(f[x0][x][y0][y1][kk])+fix(f[x][x1][y0][y1][k-kk]);
					if(now<res) res=now;
				}
				for(int y=y0+1;y<y1;y++){
					db now=fix(f[x0][x1][y0][y][kk])+fix(f[x0][x1][y][y1][k-kk]);
					if(now<res) res=now;
				}
			}
			f[x0][x1][y0][y1][k]=res;
		}
	printf("%.2lf\n",sqrt((f[0][n][0][m][o]-o)/o));
}

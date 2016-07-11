/*
f[i][l][r]=上矩形的下端
=max( f[i+1][l][r]+(r-l+1), max(l<ll<=rr<r){ g[i+1][ll][rr] } )
g[i][l][r]=中矩形的下端
=max( g[i+1][l][r]+(r-l+1), max(1<=ll<l,r<rr<=m){ h[i+1][ll][rr] } )
h[i][l][r]=下矩形的下端
=h[i+1][l][r]+(r-l+1) | -inf
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=1000000;
#define maxi(a,b) if(a<b) a=b
int n,m,map[205],tmp[205],res;
typedef int line[205];
line mem[6][205],*F=mem[0],*f=mem[1],*G=mem[2],*g=mem[3],*H=mem[4],*h=mem[5];
int main(){
	scanf("%d%d",&n,&m);
	int ans=0;
	memset(F,0x80,(n+1)*sizeof(line));
	memset(G,0x80,(n+1)*sizeof(line));
	memset(H,0x80,(n+1)*sizeof(line));
	for(int i=1;i<=n;i++,swap(F,f),swap(G,g),swap(H,h)){
		for(int j=1;j<=m;j++){
			char ch; while((ch=getchar())!='0'&&ch!='1');
			map[j]=map[j-1]+(ch=='1');
		}
		memset(f,0x80,(n+1)*sizeof(line));
		memset(g,0x80,(n+1)*sizeof(line));
		memset(h,0x80,(n+1)*sizeof(line));
		for(int l=1;l<=m;l++)
			for(int r=l;r<=m;r++)
				f[l][r]=map[r]-map[l-1]?-inf:max(F[l][r],0)+(r-l+1);
		memset(tmp,0x80,sizeof(int)*(m+1));
		for(int l=2;l<=m-1;l++){
			res=-inf;
			for(int r=m-1;r>=l;r--){
				maxi(tmp[r+1],F[l-1][r+1]);
				maxi(res,tmp[r+1]);
				g[l][r]=map[r]-map[l-1]?-inf:max(G[l][r],res)+(r-l+1);
			}
		}
		memset(tmp,0x80,sizeof(int)*(m+1));
		for(int l=m-2;l>=1;l--){
			res=-inf;
			for(int r=l+2;r<=m;r++){
				maxi(tmp[r-1],G[l+1][r-1]);
				maxi(res,tmp[r-1]);
				h[l][r]=map[r]-map[l-1]?-inf:max(H[l][r],res)+(r-l+1);
				maxi(ans,h[l][r]);
			}
		}
	}
	printf("%d\n",ans);
}

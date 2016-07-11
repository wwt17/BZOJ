#include <cstdio>
#include <algorithm>
using std::max;
#define sqr(x) (x)*(x)
const int M=1005;
int n,m,g[M][M],q[M],f[M][M];
int main(){
	scanf("%d%d",&n,&m);
	while(n--){
		static int x,y,v;
		scanf("%d%d%d",&x,&y,&v);
		g[x][y]+=v;
	}
	q[1]=1;
	for(int i=1;i<=m;i++){
		int last=1;
		for(int j=1;j<=m;j++) if(g[i][j]){
			int tmp=-2000000000;
			for(;last<=j;last++) if(q[last])
				tmp=max(tmp,f[q[last]][last]-sqr(q[last]-i)-sqr(last-j));
			q[last=j]=i;
			f[i][j]=tmp+g[i][j];
		}
	}
	printf("%d\n",f[m][m]);
}

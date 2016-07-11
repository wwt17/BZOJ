/*
首先注意到，整个矩阵可以由第0行和第0列确定
先构出一组不保证合法的解 
搜索[0][0]和第0行的数，对于每个元素要满足 
ans[i][j]=g[i][j]+g[0][0]*(-1)^(i+j-1)+g[0][j]*(-1)^i+g[i][0]*(-1)^j
（考虑第0行和第0列对i,j的影响） 
由于ans[i][j]的范围限定，可推知g[i][0]的范围限定
如g[i][0]无解，则剪枝 
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=205,sign[2]={1,-1};
int n,m,p,g[N][N],l[N][N],r[N][N];
void dfs(int j){
	if(j==m){
		for(int i=1;i<n;i++)
			g[i][0]=l[i][m-1];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				printf("%d%c",i&&j?g[i][j]+g[0][0]*sign[(i+j-1)&1]+g[0][j]*sign[i&1]+g[i][0]*sign[j&1]:g[i][j]," \n"[j==m-1]);
		exit(0);
	}
	for(g[0][j]=0;g[0][j]<p;g[0][j]++){
		bool ok=true;
		for(int i=1;i<n;i++){
			int	bot=(0-(g[i][j]+g[0][0]*sign[(i+j-1)&1]+g[0][j]*sign[i&1]))*sign[j&1],
				top=(p-1-(g[i][j]+g[0][0]*sign[(i+j-1)&1]+g[0][j]*sign[i&1]))*sign[j&1];
			if(top<bot) swap(top,bot);
			l[i][j]=max(l[i][j-1],bot);
			r[i][j]=min(r[i][j-1],top);
			if(l[i][j]>r[i][j]){
				ok=false;
				break;
			}
		}
		if(ok)
			dfs(j+1);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			scanf("%d",&g[i][j]);
			if(i&&j) g[i][j]-=g[i-1][j]+g[i][j-1]+g[i-1][j-1];
		}
	for(int i=1;i<n;i++)
		l[i][0]=0,r[i][0]=p-1;
	for(g[0][0]=0;g[0][0]<p;g[0][0]++)
		dfs(1);
}

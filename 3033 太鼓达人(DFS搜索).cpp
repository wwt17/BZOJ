#include <cstdio>
const int N=11;
int n,ans[1<<N];
bool vis[1<<N];
bool dfs(int x,int depth){
	if(depth==(1<<n))
		return !x;
	if(vis[x]) return false;
	vis[x]=true;
	ans[depth]=x;
	if(dfs(x<<1&((1<<n)-1)  ,depth+1))
		return true;
	if(dfs(x<<1&((1<<n)-1)|1,depth+1))
		return true;
	vis[x]=false;
	return false;
}
int main(){
	scanf("%d",&n);
	dfs(0,0);
	printf("%d ",1<<n);
	for(int i=0;i<1<<n;i++) printf("%d",ans[i]>>n-1);
	puts("");
}

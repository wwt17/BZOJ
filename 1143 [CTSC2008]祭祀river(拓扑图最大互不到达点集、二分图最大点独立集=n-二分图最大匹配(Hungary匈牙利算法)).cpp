#include <cstdio>
const int N=105,M=1000;
int n,m;
struct edge{
	int ed;
	edge *next;
} E[M];
edge *son[N];
bool *vis,arr[N][N],used[N];
int mat[N];
void dfs(int u){
	if(vis[u]) return;
	vis[u]=true;
	for(edge *e=son[u];e;e=e->next)
		dfs(e->ed);
}
bool extend(int u){
	if(!u) return true;
	for(int v=1;v<=n;v++) if(!used[v]&&arr[u][v]){
		used[v]=true;
		if(extend(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u;
		scanf("%d%d",&u,&E[i].ed);
		E[i].next=son[u];
		son[u]=E+i;
	}
	for(int u=1;u<=n;u++){
		vis=arr[u];
		dfs(u);
		arr[u][u]=false;
	}
	int ans=n;
	for(int u=1;u<=n;u++){
		for(int v=1;v<=n;v++) used[v]=false;
		if(extend(u))
			ans--;
	}
	printf("%d\n",ans);
	scanf("\n");
}

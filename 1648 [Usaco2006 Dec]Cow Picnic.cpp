#include <cstdio>
#include <cstring>
#define size 1001
struct edge {
	int link;
	edge* next;
	edge(int _link,edge* _next):link(_link),next(_next) {} 
} *son[size];
int f[size];
bool vis[size];
void DFS(int v) {
	if (vis[v]) return;
	vis[v]=true;
	++f[v];
	for (edge* e=son[v];e;e=e->next)
		 DFS(e->link);
}
int main() {
	int K,N,M,i,p[100],a,b;
	scanf("%d%d%d",&K,&N,&M);
	for (i=0;i<K;++i) scanf("%d",&p[i]);
	while (M--) {
		scanf("%d%d",&a,&b); 
		son[a]=son[0]=new edge(b,son[a]);
	}
	for (i=0;i<K;++i) {
		memset(vis,0,N+1);
		DFS(p[i]);
	}
	int ans=0;
	for (i=1;i<=N;++i) if (f[i]==K) ++ans;
	printf("%d\n",ans);
	scanf("%d");
}

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=10005,M=1000005,S=205;
const double inf=1e50,eps=1e-9;
int n,m,s,t,son[N],ed[M],next[M],son2[N],ed2[M],next2[M];
int len,dfn[N],low[N],belong[N],lab[N],num,mem[N],st[N];
bool instack[N];
int top,stack[N];
int deg[N],head,tail,q[N];
int size;
double ans[N],mat[S][S];
void tarjan(int u){
	dfn[u]=low[u]=++len;
	stack[top++]=u;
	instack[u]=true;
	for(int e=son[u];e;e=next[e]){
		int v=ed[e];
		if(dfn[v]){
			if(instack[v]) low[u]=min(low[u],dfn[v]);
			continue;
		}
		tarjan(v);
		low[u]=min(low[u],low[v]);
	}
	if(low[u]==dfn[u]){
		num++;
		st[num]=st[num-1];
		do{
			int v=stack[--top];
			instack[v]=false;
			belong[v]=num;
			mem[++st[num]]=v;
			lab[v]=st[num]-st[num-1];
		}while(stack[top]!=u);
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int e=1;e<=m;e++){
		int u,v; scanf("%d%d",&u,&v);
		
		ed[e]=v;
		next[e]=son[u];
		son[u]=e;
		
		ed2[e]=u;
		next2[e]=son2[v];
		son2[v]=e;
	}
	for(int i=1;i<=n;i++) if(!dfn[i])
		tarjan(i);
	for(int u=1;u<=n;u++)
		for(int e=son[u];e;e=next[e]){
			int v=ed[e];
			if(belong[u]!=belong[v])
				deg[belong[u]]++;
		}
	for(int i=1;i<=num;i++) if(!deg[i]) q[tail++]=i;
	while(head<tail){
		int x=q[head++];
		size=st[x]-st[x-1];
		for(int i=1;i<=size;i++){
			for(int j=1;j<=size+1;j++) mat[i][j]=0;
			int u=mem[st[x-1]+i];
			if(u==t){
				mat[i][i]=1;
				continue;
			}
			for(int e=son[u];e;e=next[e]){
				mat[i][i]+=1;
				mat[i][size+1]+=1;
				if(belong[ed[e]]!=belong[u])
					mat[i][size+1]+=ans[ed[e]];
				else
					mat[i][lab[ed[e]]]-=1;
			}
		}
		bool ok=true;
		for(int i=1;i<=size;i++){
			for(int j=i;j<=size;j++) if(fabs(mat[i][j])>eps){
				for(int k=size+1;k>=i;k--) swap(mat[i][k],mat[j][k]);
				break;
			}
			if(fabs(mat[i][i])<=eps){
				ok=false;
				break;
			}
			for(int k=size+1;k>=i;k--) mat[i][k]/=mat[i][i];
			for(int j=1;j<=size;j++) if(j!=i)
				for(int k=size+1;k>=i;k--) mat[j][k]-=mat[j][i]*mat[i][k];
		}
		for(int i=1;i<=size;i++){
			int u=mem[st[x-1]+i];
			if(ok)
				ans[u]=mat[i][size+1]/mat[i][i];
			else
				ans[u]=inf;
			for(int e=son2[u];e;e=next2[e]){
				int v=ed2[e];
				if(!--deg[belong[v]]) q[tail++]=belong[v];
			}
		}
	}
	if(ans[s]>=inf/10)
		puts("INF");
	else
		printf("%.3lf\n",ans[s]);
}

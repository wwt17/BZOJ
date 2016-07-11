#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N=2005,M=10005;
int n,m,t,cur,newE,last[N],son[N],ed[M],next[M],deg[N];
vector<int> ok[N];
queue<int> q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&last[i]);
	for(int i=0;i<m;i++){
		int a,b; scanf("%d%d",&a,&b);
		ed[++newE]=a; next[newE]=son[b]; son[b]=newE;
	}
	for(cur=1;cur<=n;cur++){
		for(int v=1;v<=n;v++) deg[v]=0;
		for(int e=1;e<=newE;e++) deg[ed[e]]++;
		for(t=1;t<=n;t++) ok[t].clear();
		for(int v=1;v<=n;v++) if(!deg[v])
			ok[last[v]].push_back(v);
		t=n;
		for(vector<int>::iterator it=ok[t].begin();it!=ok[t].end();it++)
			q.push(*it);
		while(!q.empty()){
			int u=q.front(); q.pop();
			if(u==cur) continue;
			t--;
			for(vector<int>::iterator it=ok[t].begin();it!=ok[t].end();it++)
				q.push(*it);
			for(int e=son[u];e;e=next[e]) if(!--deg[ed[e]]){
				int v=ed[e];
				if(last[v]<t)
					ok[last[v]].push_back(v);
				else
					q.push(v);
			}
		}
		printf("%d ",t);
	}
}

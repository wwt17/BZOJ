#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
int tim,m,es,n[3],b[20],v[5005][3],son[5005],ed[5005],nxt[5005],mat[5005],vis[5005];
bool extend(int u){
	if(u==-1) return true;
	for(int e=son[u];e;e=nxt[e]){
		int v=ed[e];
		if(vis[v]!=tim){
			vis[v]=tim;
			if(extend(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	int T; scanf("%d",&T);
	while(T--){
		int ans=20;
		m=0;
		rep(i,3) scanf("%d",&n[i]);
		rep(i,n[0])
			rep(j,n[1])
				rep(k,n[2]){
					int x; scanf("%d",&x);
					if(x){
						v[m][0]=i;
						v[m][1]=j;
						v[m][2]=k;
						m++;
					}
				}
		rep(i,3) rep(j,i) if(n[j]>n[i]){
			swap(n[j],n[i]);
			rep(k,m) swap(v[k][i],v[k][j]);
		}
		rep(i,n[0]) b[i]=1;
		rep(l,m) b[v[l][0]]=0;
		rep(k,1<<n[0]){
			int now=0;
			int flag=0;
			rep(i,n[0]) if(k>>i&1) now++,flag|=b[i];
			if(flag) continue;
			rep(i,n[2]) son[i]=0,mat[i]=-1;
			es=0;
			rep(l,m) if(!(k>>v[l][0]&1)){
				++es;
				ed[es]=v[l][2];
				nxt[es]=son[v[l][1]];
				son[v[l][1]]=es;
			}
			rep(i,n[1]) tim++,now+=extend(i);
			ans=min(ans,now);
		}
		printf("%d\n",ans);
	}
}

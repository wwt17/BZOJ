#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> pii;
#define fi first
#define se second
const int N=505,M=10005,inf=(int)1e9+7;

int n,m,cntx,son[N],ed[M],nex[M],w[M],dist[M][N];
bool inq[N];

int getint(){
	char c;
	while((c=getchar())<'0'||c>'9') if(c=='x') return 0;
	int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}

inline bool mini(int &a,const int b){
	return b<a?(a=b,true):false;
}

void spfa(int s){
	for(int k=0;k<=cntx;k++)
		for(int i=1;i<=n;i++) dist[k][i]=inf;
	static int q[N];
	dist[0][s]=0;
	for(int k=0;k<=cntx;k++){
		int head=0,tail=0;
		for(int i=1;i<=n;i++) if(dist[k][i]<inf){
			q[tail++]=i;
			inq[i]=true;
		}
		while(head!=tail){
			int u=q[head++]; inq[u]=false;
			for(int e=son[u];e;e=nex[e]) if(w[e]){
				int v=ed[e];
				if(mini(dist[k][v],dist[k][u]+w[e]))
					if(!inq[v]){
						q[tail++]=v;
						inq[ed[e]]=true;
					}
			}
		}
		if(k<cntx)
		for(int u=1;u<=n;u++){
			for(int e=son[u];e;e=nex[e]) if(!w[e])
				mini(dist[k+1][ed[e]],dist[k][u]);
		}
	}
}

inline int calc(pii u,pii v){
	int a=v.se-u.se,b=u.fi-v.fi,t=a%b;
	if(t<0) t+=b;
	return (a-t)/b;
}
inline ll sum(pii u,int x){
	return u.se*1ULL*x+x*(x+1ULL)/2ULL*u.fi;
}

int main(){
	n=getint(),m=getint();
	for(int e=1;e<=m;e++){
		int x=getint(),y=getint(); w[e]=getint();
		ed[e]=y;
		nex[e]=son[x];
		son[x]=e;
		if(!w[e]) cntx++;
	}
	int q; scanf("%d",&q);
	while(q--){
		int s,t; scanf("%d%d",&s,&t);
		spfa(s);
		bool ok=true;
		for(int k=0;k<=cntx;k++) if(dist[k][t]<inf) ok=false;
		if(ok){
			puts("0 0");
			continue;
		}
		if(dist[0][t]==inf){
			puts("inf");
			continue;
		}
		static pii line[M];
		int top=0;
		for(int k=cntx;k>=0;k--){
			pii cur(k,dist[k][t]);
			while(top>=2&&calc(line[top-2],line[top-1])>=calc(line[top-1],cur)) top--;
			line[top++]=cur;
		}
		int ans1=0;
		ll ans2=0;
		for(int i=0;i<top;i++){
			int l=max(0,i?calc(line[i-1],line[i]):0),r=max(0,i<top-1?calc(line[i],line[i+1]):l?(line[i].se-line[i-1].se)%(line[i-1].fi-line[i].fi)?l+1:l:l+1);
			ans1+=r-l;
			ans2+=sum(line[i],r)-sum(line[i],l);
		}
		printf("%d %llu\n",ans1,ans2);
	}
}

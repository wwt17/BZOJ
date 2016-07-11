#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second

const int N=3010,M=N*6,inf=(int)1e9,inf_=300005;

int n,m,nn,mm;

struct vec{
	int x,y;
} O,p[N];

int son[N],ed[M],nex[M],w[M],num[M],newe=1,ord[M];

void addedge(int u,int v,int w){
	++newe; nex[newe]=son[u]; ed[newe]=v; ::w[newe]=w; son[u]=newe;
}

bool cmp(const int i,const int j){
	return atan2(p[ed[i]].y-O.y,p[ed[i]].x-O.x)<atan2(p[ed[j]].y-O.y,p[ed[j]].x-O.x);
}

struct edge{
	int u,v,w;
} E[M];

int vis[N],in[N],pre[N],belong[N];

int directed_mst(int root){
	int ans=0;
	for(;;){
		for(int i=1;i<=n;i++) vis[i]=0,in[i]=inf,belong[i]=0;
		vis[root]=1;
		in[root]=0;
		for(int e=1;e<=m;e++){
			if(E[e].w<in[E[e].v]) in[E[e].v]=E[e].w,pre[E[e].v]=E[e].u;
		}
		for(int i=1;i<=n;i++){
			if(in[i]==inf) return inf;
			ans+=in[i];
		}
		nn=0;
		for(int i=1;i<=n;i++) if(!vis[i]){
			int u;
			for(u=i;!vis[u];u=pre[u]) vis[u]=2;
			if(u!=root&&vis[u]==2){
				++nn;
				for(;vis[u]==2;u=pre[u]){
					belong[u]=nn;
					vis[u]=1;
				}
			}
			for(u=i;vis[u]==2;u=pre[u]) vis[u]=1;
		}
		if(!nn) return ans;
		for(int i=1;i<=n;i++) if(!belong[i]) belong[i]=++nn;
		mm=0;
		for(int e=1;e<=m;e++) if(belong[E[e].u]!=belong[E[e].v]){
			edge tmp=(edge){belong[E[e].u],belong[E[e].v],E[e].w-in[E[e].v]};
			E[++mm]=tmp;
		}
		n=nn;
		m=mm;
		root=belong[root];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=1;i<=m;i++){
		int u,v,w1,w2; scanf("%d%d%d%d",&u,&v,&w1,&w2);
		if(!w1) w1=inf_;
		if(!w2) w2=inf_;
		addedge(u,v,w1);
		addedge(v,u,w2);
	}
	for(int i=1;i<=n;i++){
		O=p[i];
		int top=0;
		for(int e=son[i];e;e=nex[e]) ord[top++]=e;
		sort(ord,ord+top,cmp);
		son[i]=0;
		for(int j=top-1;j>=0;j--){
			int e=ord[j];
			nex[e]=son[i]; son[i]=e;
		}
		if(top) nex[ord[top-1]]=son[i];
	}
	int root=++nn;
	for(int i=2;i<=newe;i++) if(!num[i]){
		++nn;
		E[++mm]=(edge){root,nn,inf_};
		for(int e=i;!num[e];e=nex[e]^1){
			num[e]=nn;
			if(num[e^1]){
				if(w[e]<inf_) E[++mm]=(edge){num[e],num[e^1],w[e]};
				if(w[e^1]<inf_) E[++mm]=(edge){num[e^1],num[e],w[e^1]};
			}
		}
	}
	n=nn;
	m=mm;
	printf("%d\n",directed_mst(root)-inf_);
}

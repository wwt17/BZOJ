#include <cstdio>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

const int N=100005,R=1000005,C=R,V=N*3,E=N*10;

bool appx[R],appy[C];

struct data{
	int x,y,t;
	bool operator < (const data &B) const{
		return x<B.x||x==B.x&&y<B.y;
	}
	void read(){
		scanf("%d%d%d",&x,&y,&t);
		appx[x]=true;
		appy[y]=true;
	}
};

int n,r,c,m;

data a[V];
#define getloc(x,y) (lower_bound(a+1,a+n+1,(data){x,y,0})-a)

int son[V],next[E];

pii edge[E];

int len,low[V],dfn[V];

bool ins[V];
int stack[V];

int nn,lab[V],w[V],f[V];

int deg[V],head,tail,q[V];

void tarjan(int u){
	low[u]=dfn[u]=++len;
	stack[++*stack]=u;
	ins[u]=true;
	for(int e=son[u];e;e=next[e]){
		int v=edge[e].second;
		if(dfn[v]){
			if(ins[v])
				low[u]=min(low[u],dfn[v]);
		}
		else{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
	}
	if(low[u]==dfn[u]){
		++nn;
		while(stack[*stack]!=u){
			int v=stack[*stack];
			lab[v]=nn;
			ins[v]=false;
			--*stack;
		}
		lab[u]=nn;
		ins[u]=false;
		--*stack;
	}
}

int main(){
	scanf("%d%d%d",&n,&r,&c);
	for(int i=1;i<=n;i++) a[i].read();
	for(int i=1;i<=r;i++) if(appx[i])
		a[++n]=(data){i,-1,-1};
	for(int i=1;i<=c;i++) if(appy[i])
		a[++n]=(data){-1,i,-2};
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) if(a[i].t>0){
		if(a[i].t==1)
			edge[++m]=pii(i,getloc(a[i].x,-1));
		else
		if(a[i].t==2)
			edge[++m]=pii(i,getloc(-1,a[i].y));
		else
		if(a[i].t==3)
			for(int dx=-1;dx<=1;dx++)
				for(int dy=-1;dy<=1;dy++) if(dx||dy){
					int j=getloc(a[i].x+dx,a[i].y+dy);
					if(a[j].x==a[i].x+dx&&a[j].y==a[i].y+dy)
						edge[++m]=pii(i,j);
				}
		int j=getloc(a[i].x,-1);
		if(a[j].x==a[i].x&&a[j].y==-1)
			edge[++m]=pii(j,i);
		j=getloc(-1,a[i].y);
		if(a[j].x==-1&&a[j].y==a[i].y)
			edge[++m]=pii(j,i);
	}
	for(int i=1;i<=m;i++){
		next[i]=son[edge[i].first];
		son[edge[i].first]=i;
	}
	for(int i=1;i<=n;i++) if(!dfn[i])
		tarjan(i);
	for(int i=1;i<=n;i++) w[lab[i]]+=a[i].t>0;
	n=nn;
	for(int i=1;i<=n;i++) son[i]=0;
	for(int i=1;i<=m;i++){
		edge[i].first=lab[edge[i].first];
		edge[i].second=lab[edge[i].second];
		if(edge[i].first==edge[i].second) continue;
		next[i]=son[edge[i].first];
		son[edge[i].first]=i;
		deg[edge[i].second]++;
	}
	for(int i=1;i<=n;i++) if(!deg[i]) q[tail++]=i;
	int ans=0;
	while(head!=tail){
		int u=q[head++];
		f[u]+=w[u];
		ans=max(ans,f[u]);
		for(int e=son[u];e;e=next[e]){
			int v=edge[e].second;
			f[v]=max(f[v],f[u]);
			if(!--deg[v])
				q[tail++]=v;
		}
	}
	printf("%d\n",ans);
}

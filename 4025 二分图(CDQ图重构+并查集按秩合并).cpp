#include <cstdio>
#include <algorithm>
using namespace std;

const int N=100005,M=200005,logT=20;

int n,m,T;
int fa[N],height[N],w[N];
int x[M],y[M],st[M],en[M];
struct rec{
	int u,height;
} memrec[N*2],*newrec=memrec;
void back(rec *last){
	while(newrec>last){
		--newrec;
		fa[newrec->u]=0;
		height[newrec->u]=newrec->height;
	}
}
int link(int e){
	int u=x[e],v=y[e];
	int flag=1;
	for(;fa[u];u=fa[u]) flag^=w[u];
	for(;fa[v];v=fa[v]) flag^=w[v];
	if(u==v)
		return flag?-1:0;
	if(height[v]>height[u]) swap(u,v);
	*newrec++=(rec){v,height[v]};
	fa[v]=u;
	w[v]=flag;
	*newrec++=(rec){u,height[u]};
	height[u]=max(height[u],height[v]+1);
	return 1;
}
int edge[logT][M];

void work(int lev,int beg,int end){
	if(*edge[lev]==0){
		for(int i=beg;i<end;i++) puts("Yes");
		return;
	}
	rec *last=newrec;
	int mid=(beg+end)>>1;
	bool ok=true;
	*edge[lev+1]=0;
	for(int i=1;i<=*edge[lev];i++){
		int e=edge[lev][i];
		if(st[e]<=beg&&en[e]>=mid){
			if(link(e)==-1){
				ok=false; break;
			}
		}
		if(st[e]>beg&&st[e]<mid||en[e]>beg&&en[e]<mid)
			edge[lev+1][++*edge[lev+1]]=e;
	}
	if(ok)
		work(lev+1,beg,mid);
	else{
		for(int i=beg;i<mid;i++) puts("No");
	}
	back(last);
	ok=true;
	*edge[lev+1]=0;
	for(int i=1;i<=*edge[lev];i++){
		int e=edge[lev][i];
		if(st[e]<=mid&&en[e]>=end){
			if(link(e)==-1){
				ok=false; break;
			}
		}
		if(st[e]>mid&&st[e]<end||en[e]>mid&&en[e]<end)
			edge[lev+1][++*edge[lev+1]]=e;
	}
	if(ok)
		work(lev+1,mid,end);
	else{
		for(int i=mid;i<end;i++) puts("No");
	}
	back(last);
}

int main(){
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=m;i++) scanf("%d%d%d%d",&x[i],&y[i],&st[i],&en[i]);
	for(int i=1;i<=m;i++) edge[0][++*edge[0]]=i;
	work(0,0,T);
}

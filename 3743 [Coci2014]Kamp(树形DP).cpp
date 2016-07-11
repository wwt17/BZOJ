#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=500005;
int n,k,root;
struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *pa;
	bool flag,ok;
	ll dis[2],ans;
	ll build(){
		ll len=0;
		ok=flag;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->pa=this;
			len+=v->build();
			if(!v->ok) continue;
			ok=1;
			len+=e->w;
			if(v->dis[0]+e->w>dis[0])
				dis[1]=dis[0],dis[0]=v->dis[0]+e->w;
			else
			if(v->dis[0]+e->w>dis[1])
				dis[1]=v->dis[0]+e->w;
		}
		return len;
	}
	void work(ll len,ll far){
		ans=len*2-max(far,dis[0]);
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->work(len+(v->ok?0:e->w),max(far,v->ok&&v->dis[0]+e->w==dis[0]?dis[1]:dis[0])+e->w);
		}
	}
} V[N];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	while(k--){
		scanf("%d",&root);
		V[root].flag=1;
	}
	V[root].work(V[root].build(),0);
	for(int i=1;i<=n;i++) printf("%lld\n",V[i].ans);
}

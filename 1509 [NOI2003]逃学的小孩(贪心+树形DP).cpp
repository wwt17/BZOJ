#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=200005;
int n;
ll ans;
struct node;
struct edge{
	node *ed;
	edge *next;
	ll w;
} E[N<<1],*newE=E;
struct node{
	node *pa;
	edge *son;
	ll f[3];
	void renew(ll d){
		if(d>f[2]){
			if(d>f[1]){
				f[2]=f[1];
				if(d>f[0]){
					f[1]=f[0];
					f[0]=d;
				}
				else
				f[1]=d;
			}
			else
			f[2]=d;
		}
	}
	void dfs(){
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->pa=this;
			v->dfs();
			renew(v->f[0]+e->w);
		}
	}
	void dfs2(ll d){
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->dfs2(max(d,f[v->f[0]+e->w==f[0]])+e->w);
		}
		renew(d);
		if(f[1]) ans=max(ans,f[0]+f[1]*2+f[2]);
	}
} V[N];
int main(){
	scanf("%d%*d",&n);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	V[1].dfs();
	V[1].dfs2(0);
	printf("%lld\n",ans);
}

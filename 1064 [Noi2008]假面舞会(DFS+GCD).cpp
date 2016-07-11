#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100005,M=1000005;
int n,m,mo,Max,Min,tot;
int gcd(const int a,const int b){
	return b?gcd(b,a%b):a;
}
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	bool vis;
	int level;
	void dfs(){
		vis=1;
		Max=max(Max,level);
		Min=min(Min,level);
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			int t=level+(e-E&1?-1:1);
			if(!v->vis){
				v->level=t;
				v->dfs();
			}
			else
				mo=gcd(mo,abs(t-v->level));
		}
	}
} V[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int a,b; scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	for(int i=1;i<=n;i++) if(!V[i].vis){
		Max=Min=0;
		V[i].dfs();
		tot+=Max-Min+1;
	}
	if(mo){
		if(mo<3) return puts("-1 -1"),0;
		int t=3;
		for(;t<=mo&&mo%t;t++);
		printf("%d %d\n",mo,t);
	}
	else{
		if(tot<3) return puts("-1 -1"),0;
		printf("%d 3\n",tot);
	}
}

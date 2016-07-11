/*
确定一个点后整张图就确定了。
hash求众数 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=500005,Mo[2]={(int)1e9+7,(int)1e9+21};

int n,mo,*top,seq[N];

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	int a,dg;
	void dfs(node *fa,long long w){
		*top++=a*w%mo;
		w=w*(dg-1)%mo;
		for(edge *e=son;e;e=e->next) if(e->ed!=fa)
			e->ed->dfs(this,w);
	}
} V[N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&V[i].a);
	for(int i=2;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
		V[x].dg++;
		V[y].dg++;
	}
	V[1].dg++;
	int ans=n;
	for(int j=0;j<2;j++){
		mo=Mo[j];
		int now=0;
		top=seq;
		V[1].dfs(NULL,1);
		sort(seq,top);
		for(int i=0,j;i<n;i=j){
			for(j=i;seq[j]==seq[i];j++);
			if(j-i>now) now=j-i;
		}
	//	for(int i=0;i<n;i++) printf("%d ",seq[i]); puts("");
		if(now<ans) ans=now;
	}
	printf("%d\n",n-ans);
}

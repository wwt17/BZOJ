#include <cstdio>
#include <algorithm>
using namespace std;

const int N=300005;

int n,s;

struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
node *tmp;
int best;
struct node{
	node *fa;
	edge *son;
	int dis,far[2];
	void dfs(){
		if(dis>best){
			best=dis;
			tmp=this;
		}
		far[0]=far[1]=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=fa){
			e->ed->fa=this;
			e->ed->dis=dis+e->w;
			e->ed->dfs();
			int now=e->w+e->ed->far[0];
			if(now>far[0]) far[1]=far[0],far[0]=now; else
			if(now>far[1]) far[1]=now;
		}
	}
} V[N],*seq[N];
int len;

int head,tail;
node *q[N];

int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	best=-1;
	V[1].fa=NULL;
	V[1].dis=0;
	V[1].dfs();
	best=-1;
	tmp->fa=NULL;
	tmp->dis=0;
	tmp->dfs();
	for(len=0;tmp;tmp=tmp->fa) seq[len++]=tmp;
	reverse(seq,seq+len);
	int ans=0x7fffffff;
	for(int i=0,j=0;i<len;i++){
		for(;j<len&&seq[j]->dis-seq[i]->dis<=s;j++){
			while(head<tail&&q[tail-1]->far[1]<=seq[j]->far[1]) tail--;
			q[tail++]=seq[j];
		}
		ans=min(ans,max(q[head]->far[1],max(seq[i]->dis,seq[j-1]->far[0])));
		if(head<tail&&q[head]==seq[i]) head++;
	}
	printf("%d\n",ans);
}

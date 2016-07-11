#include <cstdio>
#include <algorithm>
using namespace std;
const int N=50005,M=N*2,inf=(int)1e9;
int n,m,k,cnt,ans;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	node *from,*next;
	int num,low,dis;
	void work();
	void dfs(int _num){
		low=num=_num;
		for(edge *e=son;e;e=e->next) if(e->ed!=from){
			node *v=e->ed;
			if(v->num){
				if(v->num<low) low=v->num;
				continue;
			}
			v->dfs(num+1);
			if(v->low<num){
				low=v->low;
				next=v;
			}
			else{
				node *tmp=next;
				next=v;
				work();
				next=tmp;
			}
		}
	}
} V[N];
int calc(int x,int mo){
	return x>0?x:x+mo;
}
void node::work(){
	int res=0;
	static node *t[N];
	static int q[N*2];
	int cnt=0,head=0,tail=0;
	for(node *v=this;v;v=v->next){
		t[cnt]=v;
		while(head<tail&&t[q[tail-1]]->dis+(cnt-q[tail-1])<=v->dis) tail--;
		q[tail++]=cnt;
		cnt++;
	}
	for(int i=0;i<cnt;i++){
		while(head<tail&&(q[head]==i||calc(i-q[head],cnt)>calc(q[head]-i,cnt))) head++;
		if(head<tail) ans=max(ans,t[q[head]]->dis+calc(i-q[head],cnt)+t[i]->dis);
		while(head<tail&&t[q[tail-1]]->dis+calc(i-q[tail-1],cnt)<=t[i]->dis) tail--;
		q[tail++]=i;
		res=max(res,t[i]->dis+min(i,cnt-i));
	}
	dis=max(dis,res);
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d",&k);
		int u,v;
		scanf("%d",&u);
		while(--k){
			scanf("%d",&v);
			*newE=(edge){V+v,V[u].son},V[u].son=newE++;
			*newE=(edge){V+u,V[v].son},V[v].son=newE++;
			u=v;
		}
	}
	V[1].dfs(1);
	printf("%d\n",ans);
}

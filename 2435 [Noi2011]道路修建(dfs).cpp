#include <cstdio>
inline long long abs(int x){
	return x<0?-x:x;
}
const int N=1000005;
int n;
long long ans;
struct node;
struct edge{
	node *ed;
	edge *next;
	int c;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *pa;
	int size;
	void dfs(){
		size=1;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->dfs();
			size+=e->ed->size;
			ans+=e->c*abs(e->ed->size*2-n);
		}
	}
} V[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b,c; scanf("%d%d%d",&a,&b,&c);
		*newE=(edge){V+b,V[a].son,c},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son,c},V[b].son=newE++;
	}
	V[1].dfs();
	printf("%lld\n",ans);
}

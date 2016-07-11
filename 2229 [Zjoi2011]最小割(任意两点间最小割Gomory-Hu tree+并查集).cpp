#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef unsigned ll;
const int N=155,M=3005;
const ll inf=4e9;
int n,m,c[M];
int now;
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[M<<1],*newE=E;
int Flag;
struct node{
	edge *son;
	int flag;
	int depth;
	int size;
	node *belong;
	node* get(){
		return belong?(belong=belong->get()):this;
	}
} V[N];
void addedge(node *u,node *v,int c){
	*newE=(edge){v,u->son,c},u->son=newE++;
	*newE=(edge){u,v->son,c},v->son=newE++;
}
bool cmp(const node *u,const node *v){
	return u->flag>v->flag;
}
node *S,*T,*seq[N];
bool layer(node **beg,node **end){
	for(node **it=beg;it<end;it++){
		node *u=*it;
		u->depth=0;
	}
	queue<node*> q;
	S->depth=1;
	q.push(S);
	while(!q.empty()){
		node *u=q.front(); q.pop();
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(!v->depth){
				v->depth=u->depth+1;
				if(v==T) return true;
				q.push(v);
			}
		}
	}
	return false;
}
ll flow(node *u,ll f){
	if(u==T) return f;
	ll left=f;
	for(edge *e=u->son;e&&left;e=e->next) if(e->cap&&e->ed->depth==u->depth+1){
		ll tmp=flow(e->ed,min(left,ll(e->cap)));
		e->cap-=tmp;
		E[e-E^1].cap+=tmp;
		left-=tmp;
	}
	if(left==f) u->depth=0;
	return f-left;
}
void dfs(node *u){
	if(u->flag==Flag) return;
	u->flag=Flag;
	for(edge *e=u->son;e;e=e->next) if(e->cap)
		dfs(e->ed);
}
int cnt;
struct data{
	node *u,*v; ll w;
	friend bool operator < (const data &a,const data &b){
		return a.w<b.w;
	}
	void work(){
		node *x=u->get(),*y=v->get();
		now+=x->size*y->size;
		y->size+=x->size;
		x->belong=y;
	}
} res[N];
void work(node **beg,node **end){
	S=beg[0]; T=end[-1];
	if(S==T) return;
	newE=E;
	for(int i=0;i<m;i++) (newE++)->cap=c[i],(newE++)->cap=c[i];
	ll ans=0;
	while(layer(seq+1,seq+n+1)){
		ll f;
		while(f=flow(S,inf))
			ans+=f;
	}
	Flag++;
	dfs(S);
	sort(beg,end,cmp);
	node **mid=lower_bound(beg,end,T,cmp);
	res[cnt++]=(data){S,T,ans};
	work(beg,mid);
	work(mid,end);
}
int q;
int ans[N];
void Main(){
	scanf("%d%d",&n,&m);
	newE=E;
	Flag=0;
	for(int i=1;i<=n;i++) V[i].son=NULL,V[i].flag=0;
	for(int i=0;i<m;i++){
		int a,b; scanf("%d%d%d",&a,&b,&c[i]);
		addedge(V+a,V+b,c[i]);
	}
	for(int i=1;i<=n;i++) seq[i]=V+i;
	cnt=0;
	work(seq+1,seq+n+1);
	for(int i=1;i<=n;i++) V[i].belong=NULL,V[i].size=1;
	sort(res,res+cnt);
	ans[cnt]=now=0;
	for(int i=cnt-1;i>=0;i--){
		res[i].work();
		ans[i]=now;
	}
	int q; scanf("%d",&q);
	while(q--){
		int x; scanf("%d",&x);
		printf("%d\n",ans[0]-ans[upper_bound(res,res+cnt,(data){NULL,NULL,x})-res]);
	}
}
int main(){
	int T; scanf("%d",&T);
	while(T--){
		Main();
		if(T) puts("");
	}
}

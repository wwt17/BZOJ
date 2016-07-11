/*
DFS序后
区间线段树（或树状数组）套权值线段树维护原树中节点到根路径上的权值集合
修改只影响子树中的节点 O(log^2N)
询问经拆分后只需询问单点 O(log^2N) 
故使用线段树支持修改 
时间复杂度 O((N+Q)log^2N)
空间复杂度 O(Nlog^2N)
* 权值线段树即函数式线段树即主席树 
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
const int N=80005,Q=N,logN=17;
int n,q,ord[N+Q],L=0,R;
#define numof(x) lower_bound(ord+L,ord+R,x,greater<int>())-ord
typedef int type;
struct tree{
	tree *l,*r; int cnt;
	tree():l(NULL),r(NULL),cnt(0){
	}
} *t[N];
type X; int num;
void insert(tree* &cur,type beg,type end){
	if(!cur) cur=new tree;
	cur->cnt+=num;
	if(end-beg>1){
		type mid=beg+(end-beg)/2;
		if(X<mid)
			insert(cur->l,beg,mid);
		else
			insert(cur->r,mid,end);
	}
}
void inc(int x){
	for(;x<=n+1;x+=x&-x) insert(t[x],L,R);
}
struct data;
struct node{
	vector<node*> next; node *pa; int w;
	int st,en;
	vector<data*> query;
	node *belong;
	bool vis;
	node *get(){
		if(!belong) return this;
		return belong=belong->get();
	}
	void dfs();
} V[N];
struct data{
	int k,a,b; node *lca;
	void read(){
		scanf("%d%d%d",&k,&a,&b);
		if(k==0)
			ord[R++]=b;
		else{
			V[a].query.push_back(this);
			V[b].query.push_back(this);
		}
	}
	void work(){
		if(k==0){
			X=V[a].w;
			num=-1,inc(V[a].st);
			num=+1,inc(V[a].en+1);
			X=V[a].w=b=numof(b);
			num=+1,inc(V[a].st);
			num=-1,inc(V[a].en+1);
		}
		else{
			static tree *seq[3*logN];
			static int w[3*logN];
			int cnt=0;
			for(int x=V[a].st;x;x-=x&-x){
				seq[cnt]=t[x];
				w[cnt]=1;
				cnt++;
			}
			for(int x=V[b].st;x;x-=x&-x){
				seq[cnt]=t[x];
				w[cnt]=1;
				cnt++;
			}
			for(int x=lca->st;x;x-=x&-x){
				seq[cnt]=t[x];
				w[cnt]=-2;
				cnt++;
			}
			type beg=L,end=R;
			int now=beg<=lca->w&&lca->w<end;
			for(int i=0;i<cnt;i++)
				now+=(seq[i]?seq[i]->cnt:0)*w[i];
			if(now<k){
				puts("invalid request!");
				return;
			}
			while(end-beg>1){
				type mid=beg+(end-beg)/2;
				int now=beg<=lca->w&&lca->w<mid;
				for(int i=0;i<cnt;i++)
					now+=(seq[i]&&seq[i]->l?seq[i]->l->cnt:0)*w[i];
				if(k<=now){
					for(int i=0;i<cnt;i++)
						if(seq[i]) seq[i]=seq[i]->l;
					end=mid;
				}
				else{
					for(int i=0;i<cnt;i++)
						if(seq[i]) seq[i]=seq[i]->r;
					k-=now;
					beg=mid;
				}
			}
			printf("%d\n",ord[beg]);
		}
	}
} s[Q];
void node::dfs(){
	static int len=0;
	st=++len;
	for(vector<node*>::iterator e=next.begin();e!=next.end();e++){
		node *v=*e;
		if(v==pa) continue;
		v->pa=this;
		v->dfs();
	}
	en=len;
	X=w=numof(w);
	num=+1,inc(st);
	num=-1,inc(en+1);
	vis=true;
	for(vector<data*>::iterator e=query.begin();e!=query.end();e++){
		data *q=*e;
		node *v=V+q->a==this?V+q->b:V+q->a;
		if(!v->vis) continue;
		q->lca=v->get();
	}
	belong=pa;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&V[i].w);
		ord[R++]=V[i].w;
	}
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		V[x].next.push_back(V+y);
		V[y].next.push_back(V+x);
	}
	for(int i=0;i<q;i++)
		s[i].read();
	sort(ord,ord+R,greater<int>());
	R=unique(ord,ord+R)-ord;
	V[1].pa=V;
	V[1].dfs();
	for(int i=0;i<q;i++)
		s[i].work();
}

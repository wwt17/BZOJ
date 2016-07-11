#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N=200005,K=500005;
long long ans;
int n,m,k,tim,g[N],flag[N];
struct act{
	int a,b;
} a[K];
vector<act*> s[N],r[N];
struct node{
	node *l,*r;
	int t,loc;
	node *belong;
	node* get(){
		if(!belong) return this;
		return belong=belong->get();
	}
	void dfs();
} mem[N*2],*newnode=mem,*t[N],*tt[N];
void node::dfs(){
	if(!loc){
		l->dfs();
		l->belong=this;
		r->dfs();
		r->belong=this;
		return;
	}
	flag[loc]=tim;
	for(vector<act*>::iterator i=s[loc].begin();i!=s[loc].end();i++){
		act *cur=*i;
		int x=cur->a!=loc?cur->a:cur->b;
		if(flag[x]==tim)
			::r[tt[x]->get()->t].push_back(cur);
	}
}
inline node* merge(node *a,node *b,int tim){
	node *cur=newnode++;
	cur->l=a;
	cur->r=b;
	cur->t=tim;
	return cur;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",g+i);
		t[i]=newnode++;
		t[i]->loc=i;
		tt[i]=t[i];
	}
	for(int i=0;i<m;i++){
		int a,b; scanf("%d%d",&a,&b);
		t[b]=merge(t[a],t[b],i);
		t[a]=NULL;
	}
	for(int i=0;i<k;i++){
		scanf("%d%d",&a[i].a,&a[i].b);
		s[a[i].a].push_back(a+i);
		s[a[i].b].push_back(a+i);
	}
	for(tim=1;tim<=n;tim++) if(t[tim]) t[tim]->dfs();
	for(int i=0;i<m;i++){
		sort(r[i].begin(),r[i].end());
		for(vector<act*>::iterator it=r[i].begin();it!=r[i].end();it++){
			act *cur=*it;
			int x=min(g[cur->a],g[cur->b]);
			g[cur->a]-=x;
			g[cur->b]-=x;
			ans+=x*2;
		}
	}
	printf("%lld\n",ans);
}

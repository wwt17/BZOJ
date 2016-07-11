#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001;
int n,m;
long long ans=0;
inline int getint(){
	int c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
struct node *null;
struct node{
	node *pa,*l,*r,*s; int cost,lead,sum,cnt;
	void read();
	void work();
} V[N];
node *merge(node *a,node *b){
	if(a->cost<b->cost) swap(a,b);
	if(b!=null){
		a->l=merge(a->l,b);
		swap(a->l,a->r);
	}
	return a;
}
void node::read(){
	pa=V+getint();
	cost=sum=getint();
	lead=getint();
	l=r=null;
	s=this;
	cnt=1;
}
void node::work(){
	ans=max(ans,(long long)lead*cnt);
	pa->sum+=sum;
	pa->cnt+=cnt;
	pa->s=merge(pa->s,s);
	while(pa->sum>m){
		pa->sum-=pa->s->cost;
		pa->cnt--;
		pa->s=merge(pa->s->l,pa->s->r);
	}
}
int main(){
	null=V; null->s=null;
	n=getint(),m=getint();
	for(int i=1;i<=n;i++) V[i].read();
	for(int i=n;i;i--)
		V[i].work();
	printf("%I64d\n",ans);
	scanf("\n");
}

#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define x first
#define y second
const int Q=100005;
long long ans,now;
int n,m,q;
pii a[Q];
struct node *null;
typedef pair<node*,node*> pnn;
struct node{
	node *l,*r;
	int size,h;
} *root,V[40005];
#define calc(x) ((x)*((x)+1LL)>>1)
void del(node *u,node *&v){
	now-=calc(v->size)*(u->h-v->h);
	u->size-=v->size;
	v=null;
}
void add(node *u,node *v){
	now+=calc(v->size)*(u->h-v->h);
	u->size+=v->size;
}
node *build(node *beg,node *end){
	if(beg==end) return null;
	node *mid=end-(end-beg>>1);
	mid->size=end-beg;
	mid->l=build(beg,mid-1);
	mid->r=build(mid,end);
	return mid;
}
pnn split(node *cur,node *des){
	if(cur==des){
		pnn ret(cur->l,cur->r);
		del(cur,cur->l);
		del(cur,cur->r);
		return ret;
	}
	if(des<cur){
		node *tmp=cur->l;
		del(cur,cur->l);
		pnn ret=split(tmp,des);
		add(cur,cur->l=ret.y);
		ret.y=cur;
		return ret;
	}
	if(des>cur){
		node *tmp=cur->r;
		del(cur,cur->r);
		pnn ret=split(tmp,des);
		add(cur,cur->r=ret.x);
		ret.x=cur;
		return ret;
	}
}

int main(){
	null=V;
	null->l=null->r=null;
	scanf("%d%d%d",&n,&m,&q);
	for(int k=0;k<q;k++) scanf("%d%d",&a[k].x,&a[k].y);
	sort(a,a+q);
	root=build(V,V+m);
	ans=calc(n)*calc(m);
	for(int x=1,k=0;x<=n;x++){
		now+=calc(m);
		for(;k<q&&a[k].x==x;k++){
			node *u=V+a[k].y;
			pnn tmp=split(root,u);
			now-=calc(m)*(x-root->h);
			u->h=x;
			add(u,u->l=tmp.x);
			add(u,u->r=tmp.y);
			root=u;
		}
		ans-=now;
	}
	printf("%lld\n",ans);
}

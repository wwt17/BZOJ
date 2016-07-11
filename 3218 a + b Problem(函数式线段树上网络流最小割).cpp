#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N=5010,NlogN=N*14+5;
const ll inf=ll(1e15);

int n,a[N],b[N],w[N],l[N],r[N],p[N],num[N],*nums=num;

struct node;
struct edge{
	node *ed;
	edge *next;
	ll cap;
} E[(NlogN*5)<<1],*newE=E;
struct node{
	edge *son;
	ll lab;
};
struct tree{
	tree *l,*r;
	node a;
} mem[NlogN],*newtree=mem;

void addedge(node *u,node *v,ll cap0=inf,ll cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}

node S[2],*T=S+1,V[N],P[N];
tree *root;

int X,L,R;
node *f;
tree *insert(tree *cur,int beg,int end){
	tree *ret=newtree++;
	if(cur){
		ret->l=cur->l;
		ret->r=cur->r;
		addedge(&ret->a,&cur->a);
	}
	if(end-beg==1){
		f=&ret->a;
		return ret;
	}
	int mid=beg+end>>1;
	if(X<mid)
		ret->l=insert(ret->l,beg,mid);
	else
		ret->r=insert(ret->r,mid,end);
	if(ret->l)
		addedge(&ret->a,&ret->l->a);
	if(ret->r)
		addedge(&ret->a,&ret->r->a);
	return ret;
}
void query(tree *cur,int beg,int end){
	if(!cur) return;
	if(L<=beg&&end<=R){
		addedge(f,&cur->a);
		return;
	}
	int mid=beg+end>>1;
	if(L<mid)
		query(cur->l,beg,mid);
	if(mid<R)
		query(cur->r,mid,end);
}

bool layer(){
	node *q[NlogN+N],**head=q,**tail=q;
	for(tree *t=mem;t<newtree;t++)
		t->a.lab=0;
	for(int i=1;i<=n;i++)
		V[i].lab=0,
		P[i].lab=0;
	T->lab=0;
	S->lab=1;
	*tail++=S;
	while(head<tail){
		node *u=*head++;
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(!v->lab){
				v->lab=u->lab+1;
				*tail++=v;
				if(v==T) return true;
			}
		}
	}
	return false;
}
ll flow(node *u,ll F){
	if(u==T) return F;
	ll left=F;
	for(edge *e=u->son;e&&left;e=e->next) if(e->cap&&e->ed->lab==u->lab+1){
		ll f=flow(e->ed,min(left,e->cap));
		if(f){
			left-=f;
			e->cap-=f;
			E[(e-E)^1].cap+=f;
		}
	}
	if(left==F) u->lab=0;
	return F-left;
}

int main(){
	scanf("%d",&n);
	ll ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d%d%d",a+i,b+i,w+i,l+i,r+i,p+i);
		*nums++=a[i];
		ans+=b[i]+w[i];
	}
	sort(num,nums);
	nums=unique(num,nums);
	for(int i=1;i<=n;i++){
		X=lower_bound(num,nums,a[i])-num;
		L=lower_bound(num,nums,l[i])-num;
		R=upper_bound(num,nums,r[i])-num;
		f=P+i;
		query(root,0,nums-num);
		root=insert(root,0,nums-num);
		addedge(f,V+i);
		addedge(S,V+i,b[i]);
		addedge(V+i,T,w[i]);
		addedge(V+i,P+i,p[i]);
	}
	while(layer()){
		ll F;
		while(F=flow(S,inf))
			ans-=F;
	}
	printf("%lld\n",ans);
}

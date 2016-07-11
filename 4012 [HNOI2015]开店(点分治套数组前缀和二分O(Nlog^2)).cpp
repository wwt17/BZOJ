#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=150005,logN=20;

char membeg;

int n,Q,A;

struct node;
node *st;
int len;
node *seq[N];
int mem[N*(1+logN)*2],*newint=mem;
ll memll[N*(1+logN)*2],*newll=memll;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *pa;
	int level;
	int x;
	int *a,*b;
	ll *sa,*sb;
	int size,dist[logN];
	bool done;
	void dfs(int d,int lev,node *from=NULL){
		seq[++len]=this;
		dist[lev]=d;
		size=1;
		for(edge *e=son;e;e=e->next) if(!e->ed->done&&e->ed!=from){
			e->ed->dfs(d+e->w,lev,this);
			size+=e->ed->size;
		}
	}
} V[N];

bool cmp(const node *u,const node *v){
	return u->x<v->x;
}

node* getroot(node *u){
	while(true){
		node *v=NULL;
		for(edge *e=u->son;e;e=e->next) if(!e->ed->done&&e->ed->size*2>u->size){
			v=e->ed;
			break;
		}
		if(!v) break;
		int t=u->size;
		u->size-=v->size;
		v->size=t;
		u=v;
	}
	return u;
}

void dianfen(node *u,node *fa=NULL,int lev=0,int *arr=NULL,ll *sarr=NULL){
	len=0;
	u->dfs(0,lev);
	u=getroot(u);
	u->pa=fa;
	u->level=lev;
	u->b=arr;
	u->sb=sarr;
	len=0;
	u->dfs(0,lev);
	sort(seq+1,seq+len+1,cmp);
	u->a=newint; newint+=len+1;
	u->sa=newll; newll+=len+1;
	for(int i=1;i<=len;i++){
		u->a[i]=seq[i]->x;
		u->sa[i]=u->sa[i-1]+seq[i]->dist[lev];
	}
	u->done=true;
	for(edge *e=u->son;e;e=e->next) if(!e->ed->done){
		node *v=e->ed;
		len=0;
		v->dfs(e->w,lev);
		sort(seq+1,seq+len+1,cmp);
		int *a=newint; newint+=len+1;
		ll *s=newll; newll+=len+1;
		for(int i=1;i<=len;i++){
			a[i]=seq[i]->x;
			s[i]=s[i-1]+seq[i]->dist[lev];
		}
		dianfen(v,u,lev+1,a,s);
	}
}
int l,r;
inline ll query(int lev,int *a,ll *s,int val){
	while(r-l>1){
		int mid=(l+r)>>1;
		if(a[mid]<=val)
			l=mid;
		else
			r=mid;
	}
	return s[l]+1LL*l*st->dist[lev];
}

int main(){
	scanf("%d%d%d",&n,&Q,&A);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].x);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	dianfen(V+1);
	ll ans=0;
	while(Q--){
		int x;
		ll L,R;
		scanf("%d%lld%lld",&x,&L,&R);
		st=V+x;
		L=(L+ans)%A;
		R=(R+ans)%A;
		if(L>R) swap(L,R);
		L--;
		ans=0;
		for(node *u=st;u;u=u->pa){
			l=0,r=u->size+1;
			ans-=query(u->level,u->a,u->sa,L);
			r=u->size+1;
			ans+=query(u->level,u->a,u->sa,R);
			if(u->b){
				l=0,r=u->size+1;
				ans+=query(u->level-1,u->b,u->sb,L);
				r=u->size+1;
				ans-=query(u->level-1,u->b,u->sb,R);
			}
		}
		printf("%lld\n",ans);
	}
}

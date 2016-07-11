// f[u]=min{ -p[u]*d[v]+f[v] } +d[u]*p[u]+q[u]
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double real;

const int N=(int)2e5+5;
const ll inf=(ll)1e18;

int n;

struct node;
struct vec{
	ll x,y;
	vec(){
	}
	vec(ll x,ll y):x(x),y(y){
	}
};

inline real cross(const vec &c,const vec &a,const vec &b){
	return real(a.x-c.x)*(b.y-c.y)-real(b.x-c.x)*(a.y-c.y);
}

vec stack[N];
int top;

struct edge{
	node *ed;
	edge *next;
	ll l;
} E[N<<1],*newE=E;
struct node{
	node *fa;
	edge *son;
	ll p,q,e,d,f;
	int size;
	bool done;
	void init(){
		for(edge *e=son;e;e=e->next) if(e->ed!=fa){
			e->ed->d=d+e->l;
			e->ed->init();
		}
	}
	void getsize(node *from){
		size=1;
		for(edge *e=son;e;e=e->next) if(e->ed!=from&&!e->ed->done){
			e->ed->getsize(this);
			size+=e->ed->size;
		}
	}
	void renew(){
		if(top&&d-stack[top].x<=e){
			int l=0,r=top;
			while(r-l>1){
				int mid=l+r>>1;
				if(d-stack[mid].x<=e&&stack[mid].y-p*stack[mid].x>stack[mid+1].y-p*stack[mid+1].x)
					l=mid;
				else
					r=mid;
			}
			f=min(f,stack[r].y+(d-stack[r].x)*p+q);
		}
	}
} V[N],*seq[N];

int len;

bool cmp(const node *u,const node *v){
	return u->d-u->e>v->d-v->e;
}

node *getroot(node *u){
	for(;;){
		node *v=NULL;
		for(edge *e=u->son;e;e=e->next) if(!e->ed->done&&e->ed->size*2>u->size){
			v=e->ed;
			break;
		}
		if(!v) break;
		int tmp=u->size;
		u->size-=v->size;
		v->size=tmp;
		u=v;
	}
	return u;
}
void dfs(node *u){
	u->getsize(NULL);
	u=getroot(u);
	node *t=u;
	for(;t&&!t->done;t=t->fa);
	u->done=true;
	if(u->fa&&!u->fa->done)
		dfs(u->fa);
	len=0;
	seq[++len]=u;
	for(int i=1;i<=len;i++){
		node *u=seq[i];
		for(edge *e=u->son;e;e=e->next) if(!e->ed->done&&e->ed!=u->fa)
			seq[++len]=e->ed;
	}
	sort(seq+1,seq+len+1,cmp);
	int i=1;
	top=0;
	for(node *v=u->fa;v!=t;v=v->fa){
		for(;i<=len&&seq[i]->d-seq[i]->e>v->d;i++)
			seq[i]->renew();
		vec cur(v->d,v->f);
		while(top>=2&&cross(cur,stack[top],stack[top-1])<=0) top--;
		stack[++top]=cur;
	}
	for(;i<=len;i++)
		seq[i]->renew();
	for(int i=1;i<=len;i++){
		node *v=seq[i];
		if(v!=u&&v->d-v->e<=u->d)
			v->f=min(v->f,u->f+(v->d-u->d)*v->p+v->q);
	}
	for(edge *e=u->son;e;e=e->next) if(!e->ed->done&&e->ed!=u->fa)
		dfs(e->ed);
}

int main(){
	scanf("%d%*d",&n);
	for(int i=2;i<=n;i++){
		ll l;
		int f; scanf("%d%lld%lld%lld%lld",&f,&l,&V[i].p,&V[i].q,&V[i].e);
		V[i].fa=V+f;
		V[i].f=inf;
		*newE=(edge){V+i,V[f].son,l},V[f].son=newE++;
		*newE=(edge){V+f,V[i].son,l},V[i].son=newE++;
	}
	V[1].init();
	dfs(V+1);
	for(int i=2;i<=n;i++) printf("%lld\n",V[i].f);
}

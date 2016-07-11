#include <cstdio>
#include <algorithm>
using namespace std;

const int N=(int)1e5+5;

int n;

struct seg1{
	int sum[2];
	bool rev;
	void reverse(){
		swap(sum[0],sum[1]);
		rev^=1;
	}
} mem1[N*4],*topmem1=mem1;

void down1(seg1 *t,int cur){
	if(t[cur].rev){
		t[cur<<1].reverse();
		t[cur<<1|1].reverse();
		t[cur].rev=false;
	}
}

void update1(seg1 *t,int cur){
	t[cur].sum[0]=t[cur<<1].sum[0]+t[cur<<1|1].sum[0];
	t[cur].sum[1]=t[cur<<1].sum[1]+t[cur<<1|1].sum[1];
}

void build1(seg1 *t,int cur,int beg,int end){
	t[cur].rev=false;
	if(end-beg==1){
		t[cur].sum[0]=1;
		t[cur].sum[1]=0;
		return;
	}
	int mid=beg+end>>1;
	build1(t,cur<<1,beg,mid);
	build1(t,cur<<1|1,mid,end);
	update1(t,cur);
}

void modify1(seg1 *t,int cur,int beg,int end,int L,int R){
	if(end<=L||beg>=R) return;
	if(beg>=L&&end<=R){
		t[cur].reverse();
		return;
	}
	down1(t,cur);
	int mid=beg+end>>1;
	modify1(t,cur<<1,beg,mid,L,R);
	modify1(t,cur<<1|1,mid,end,L,R);
	update1(t,cur);
}

int query1(seg1 *t,int cur,int beg,int end,int L,int R){
	if(end<=L||beg>=R) return 0;
	if(beg>=L&&end<=R)
		return t[cur].sum[1];
	down1(t,cur);
	int mid=beg+end>>1;
	return query1(t,cur<<1,beg,mid,L,R)+query1(t,cur<<1|1,mid,end,L,R);
}

struct seg2{
	bool rev;
} mem2[N*4],*topmem2=mem2;

void build2(seg2 *t,int cur,int beg,int end){
	t[cur].rev=false;
	if(end-beg==1) return;
	int mid=beg+end>>1;
	build2(t,cur<<1,beg,mid);
	build2(t,cur<<1|1,mid,end);
}

void modify2(seg2 *t,int cur,int beg,int end,int L,int R){
	if(end<=L||beg>=R) return;
	if(beg>=L&&end<=R){
		t[cur].rev^=1;
		return;
	}
	int mid=beg+end>>1;
	modify2(t,cur<<1,beg,mid,L,R);
	modify2(t,cur<<1|1,mid,end,L,R);
}

bool query2(seg2 *t,int cur,int beg,int end,int L){
	if(end-beg==1)
		return t[cur].rev;
	int mid=beg+end>>1;
	if(L<=mid)
		return t[cur].rev^query2(t,cur<<1,beg,mid,L);
	else
		return t[cur].rev^query2(t,cur<<1|1,mid,end,L);
}

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *fa,*prefer,*top;
	int size,depth;
	seg1 *t1;
	seg2 *t2;
	int len,num;
	bool flag;
} V[N];

void dfs(node *u,node *fa){
	u->fa=fa;
	u->size=1;
	u->depth=u->fa->depth+1;
	u->prefer=NULL;
	for(edge *e=u->son;e;e=e->next) if(e->ed!=fa){
		dfs(e->ed,u);
		u->size+=e->ed->size;
		if(!u->prefer||e->ed->size>u->prefer->size)
			u->prefer=e->ed;
	}
}

void makechain(){
	dfs(V+1,V);
	for(node *u=V+1;u<=V+n;u++) if(u->fa->prefer!=u){
		u->len=0;
		for(node *v=u;v;v=v->prefer){
			v->num=++u->len;
			v->top=u;
		}
		u->t1=topmem1; topmem1+=u->len*4; build1(u->t1,1,0,u->len);
		u->t2=topmem2; topmem2+=u->len*4; build2(u->t2,1,0,u->len);
	}
}

node *lca(node *u,node *v){
	while(u->top!=v->top)
		if(u->top->depth>v->top->depth)
			u=u->top->fa;
		else
			v=v->top->fa;
	return u->depth<v->depth?u:v;
}

void modifychain1(node *u,node *v){
	for(;u->top!=v->top;u=u->top->fa){
		modify1(u->top->t1,1,0,u->top->len,1,u->num);
		u->top->flag^=1;
	}
	modify1(u->top->t1,1,0,u->top->len,v->num,u->num);
}

int querychain(node *u,node *v){
	int ans=0;
	for(;u->top!=v->top;){
		ans+=query1(u->top->t1,1,0,u->top->len,1,u->num);
		u=u->top;
		ans+=query2(u->fa->top->t2,1,0,u->fa->top->len,u->fa->num)^u->flag;
		u=u->fa;
	}
	ans+=query1(u->top->t1,1,0,u->top->len,v->num,u->num);
	return ans;
}

void modify1(node *u,node *v){
	node *w=lca(u,v);
	modifychain1(u,w);
	modifychain1(v,w);
}

void modify2(node *u,node *v){
	while(u->top!=v->top)
		if(u->top->depth>v->top->depth){
			if(u->prefer)
				modify1(u->top->t1,1,0,u->top->len,u->num,u->num+1);
			modify2(u->top->t2,1,0,u->top->len,0,u->num);
			u->top->flag^=1;
			u=u->top->fa;
		}
		else{
			if(v->prefer)
				modify1(v->top->t1,1,0,v->top->len,v->num,v->num+1);
			modify2(v->top->t2,1,0,v->top->len,0,v->num);
			v->top->flag^=1;
			v=v->top->fa;
		}
	if(v->depth<u->depth) swap(u,v);
	if(v->prefer)
		modify1(v->top->t1,1,0,v->top->len,v->num,v->num+1);
	modify2(v->top->t2,1,0,v->top->len,u->num-1,v->num);
	if(u->fa->prefer==u){
		modify1(u->top->t1,1,0,u->top->len,u->num-1,u->num);
	}
	else{
		u->flag^=1;
	}
}

int query(node *u,node *v){
	node *w=lca(u,v);
	int ans=querychain(u,w);
	ans+=querychain(v,w);
	return ans;
}

void Main(){
	newE=E;
	topmem1=mem1;
	topmem2=mem2;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) V[i].son=NULL,V[i].flag=false;
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	makechain();
	int q; scanf("%d",&q);
	while(q--){
		int t,x,y; scanf("%d%d%d",&t,&x,&y);
		if(t==1){
			modify1(V+x,V+y);
		}
		else
		if(t==2){
			modify2(V+x,V+y);
		}
		else{
			printf("%d\n",query(V+x,V+y));
		}
	}
}

int main(){
	int T; scanf("%d",&T);
	while(T--) Main();
}

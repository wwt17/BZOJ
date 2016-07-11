#include <cstdio>
typedef long long ll;
const int N=100005,CH=10;

int n,ch;

struct state{
	state *fa,*go[CH];
	int len;
	ll cnt;
} mem[N*20*2],*memtop=mem;

state* newstate(state* fa,int len){
	memtop->fa=fa;
	memtop->len=len;
	return memtop++;
}

state *root=newstate(NULL,0),*seq[N*20*2];
int sum[N*20*2];

state* extend(state* p,int c){
	if(p->go[c]&&p->go[c]->len==p->len+1) return p->go[c]; // important
	state *np=newstate(NULL,p->len+1);
	for(;p&&!p->go[c];p=p->fa) p->go[c]=np;
	if(!p)
		np->fa=root;
	else{
		state *q=p->go[c];
		if(q->len==p->len+1)
			np->fa=q;
		else{
			state *nq=newstate(q->fa,p->len+1);
			for(int x=0;x<ch;x++) nq->go[x]=q->go[x];
			nq->len=p->len+1;
			np->fa=nq;
			q->fa=nq;
			for(;p&&p->go[c]==q;p=p->fa) p->go[c]=nq;
		}
	}
	return np;
}

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	int c;
} V[N];

void build(state* s,node *u,node *fa=NULL){
	s=extend(s,u->c);
	for(edge *e=u->son;e;e=e->next) if(e->ed!=fa){
		build(s,e->ed,u);
	}
}

int tot,t[N];

int main(){
	scanf("%d%d",&n,&ch);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].c);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int i=1;i<=n;i++) if(V[i].son->next==NULL){
		build(root,V+i);
	}
	for(int i=0;i<memtop-mem;i++) sum[mem[i].len]++;
	for(int i=1;i<=memtop-mem;i++) sum[i]+=sum[i-1];
	for(int i=0;i<memtop-mem;i++) seq[--sum[mem[i].len]]=mem+i;
	for(int i=memtop-mem-1;i>=0;i--){
		state *u=seq[i];
		u->cnt=1;
		for(int c=0;c<ch;c++) if(u->go[c]) u->cnt+=u->go[c]->cnt;
	}
	printf("%lld\n",root->cnt-1);
}

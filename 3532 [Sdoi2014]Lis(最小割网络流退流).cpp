#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;
const int N=705,M=N*3+N*N/4;
typedef int data;
const data inf=0x7FFFFFFF;
int n,newE; data Ans=0,Flow;
struct node;
struct edge{
	int next; node *ed; data cap;
} E[M*2+2];
struct node{
	int depth,son,vis;
	node():son(0){}
} *S,*T;
inline int addedge(node *u,node *v,const data c1=inf,const data c2=0){
	int e=newE;
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
	return e;
}
void clear();
bool layer(){
	clear();
	T->depth=0;
	list<node*> q; node *u,*v;
	for(q.push_back(S),S->depth=1;!q.empty();q.pop_front())
		for(int e=(u=q.front())->son;e;e=E[e].next)
			if(E[e].cap&&!(v=E[e].ed)->depth){
				q.push_back(v),v->depth=u->depth+1;
				if(v==T) return true;
			}
	return false;
}
data flow(node* x,data F){
	if(x==T) return F;
	data left=F,Flow; node* y;
	for(int e=x->son;e&&left;e=E[e].next)
		if(E[e].cap&&x->depth+1==(y=E[e].ed)->depth&&(Flow=flow(y,min(left,E[e].cap))))
			E[e].cap-=Flow,E[e^1].cap+=Flow,left-=Flow;
	if(!(F-=left)) x->depth=0;
	return F;
}

inline int max_flow(node *s,node *t,data F=inf){
	S=s; T=t;
	data left=F,Flow;
	while(layer())
		while(Flow=flow(S,left))
			left-=Flow;
	return F-left;
}

int a[N],b[N],c[N],h[N],ord[N];

int e[N];

bool del[N];

node s[2],*t=s+1,x[N],y[N];

void clear(){
	for(int i=1;i<=n;i++) x[i].depth=y[i].depth=0;
}

inline bool cmp(const int i,const int j){
	return c[i]<c[j];
}

int tim;

bool connected(node *a,node *b){
	if(a==b) return true;
	if(a->vis==tim) return false;
	a->vis=tim;
	for(int e=a->son;e;e=E[e].next) if(E[e].cap)
		if(connected(E[e].ed,b))
			return true;
	return false;
}

void work(){
	scanf("%d",&n);
	newE=2;
	s->son=0;
	t->son=0;
	for(int i=1;i<=n;i++){
		x[i].son=0;
		y[i].son=0;
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	int best=0;
	for(int i=1;i<=n;i++){
		h[i]=0;
		for(int j=1;j<=i-1;j++) if(a[j]<a[i]&&h[j]>h[i]) h[i]=h[j];
		h[i]++;
		if(h[i]>best) best=h[i];
	}
	for(int i=1;i<=n;i++){
		e[i]=addedge(x+i,y+i,b[i]);
		if(h[i]==1) addedge(s,x+i);
		if(h[i]==best) addedge(y+i,t);
		for(int j=1;j<=i-1;j++) if(h[i]==h[j]+1)
			addedge(y+j,x+i);
	}
	int ans=max_flow(s,t);
	for(int i=1;i<=n;i++) ord[i]=i;
	sort(ord+1,ord+n+1,cmp);
	int cnt=0;
	for(int j=1;j<=n;j++){
		int i=ord[j];
		tim++;
		if(E[e[i]].cap||connected(x+i,y+i)){
			del[i]=0;
			continue;
		}
		cnt+=del[i]=1;
		data c=E[e[i]^1].cap;
		max_flow(t,y+i,c);
		max_flow(x+i,s,c);
		E[e[i]^1].cap=0;
		}
	printf("%d %d\n",ans,cnt);
	bool first=true;
	for(int i=1;i<=n;i++) if(del[i]){
		if(first) first=false; else putchar(' ');
		printf("%d",i);
	}
	puts("");
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		work();
}

/*
树链剖分
L,R belong to [0,1]
a[L][R]:从L到R如能走通则为最多能走的冰块数，否则为-inf 
b[0][L]:从L往右能走的最多冰块数
b[1][R]:从R往左能走的做多冰块数 
线段合并
a[L][R]=max{l.a[L][mid]+r.a[mid][R]}
b[0][L]=max{l.b[0][L],l.a[L][mid]+r.b[0][mid]}
b[1][R]=max{r.b[1][R],r.a[mid][R]+l.b[1][mid]}
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=30001,inf=100000000;
int n,m;
struct seg{
	int a[2][2],b[2][2];
	void readmap(){
		static char map[3];
		scanf("%s",map);
		for(int L=0;L<2;L++)
			for(int R=0;R<2;R++)
				a[L][R]=map[L]=='.'&&map[R]=='.'?(L^R)+1:-inf;
		for(int i=0;i<2;i++)
			b[0][i]=b[1][i]=map[i]=='.'?1+(map[!i]=='.'):0;
	}
	void init(){
		for(int L=0;L<2;L++)
			for(int R=0;R<2;R++)
				a[L][R]=L!=R?-inf:0,
				b[L][R]=0;
	}
	friend seg operator + (const seg &l,const seg &r){
		seg c;
		for(int L=0;L<2;L++)
			for(int R=0;R<2;R++)
				c.a[L][R]=max(-inf,max(l.a[L][0]+r.a[0][R],l.a[L][1]+r.a[1][R]));
		for(int i=0;i<2;i++)
			c.b[0][i]=max(l.b[0][i],max(l.a[i][0]+r.b[0][0],l.a[i][1]+r.b[0][1])),
			c.b[1][i]=max(r.b[1][i],max(r.a[0][i]+l.b[1][0],r.a[1][i]+l.b[1][1]));
		return c;
	}
	void reverse(){
		swap(a[0][1],a[1][0]);
		for(int i=0;i<2;i++) swap(b[0][i],b[1][i]);
	}
	int ans(){
		return max(b[0][0],b[0][1]);
	}
} mem[N*6],*newseg=mem-1;
void update(seg *a,int x){
	a[x]=a[x<<1]+a[x<<1|1];
}
seg query(seg *a,int l,int r){
	seg lsum,rsum;
	lsum.init();
	rsum.init();
	for(;l^r^1;l>>=1,r>>=1){
		if(!(l&1)) lsum=lsum+a[l^1];
		if(  r&1 ) rsum=a[r^1]+rsum;
	}
	return lsum+rsum;
}
struct node;
struct edge{
	node *ed; edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son; node *pa,*prefer,*top; int size,depth,loc; seg *a;
	void renew(){
		a[loc].readmap();
		for(int x=loc>>1;x;x>>=1) update(a,x);
	}
	void build(){
		size=1;
		int maxsize=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->depth=depth+1;
			e->ed->build();
			size+=e->ed->size;
			if(e->ed->size>maxsize){
				maxsize=e->ed->size;
				prefer=e->ed;
			}
		}
	}
} V[N];
void makechain(node *begin,node *end){
	for(node *u=begin;u<end;u++) if(u->pa->prefer!=u){
		int cnt=0;
		for(node *v=u;v;v=v->prefer) cnt++,v->top=u,v->a=newseg;
		int base=1; for(;base<cnt+2;base++);
		cnt=0;
		for(node *v=u;v;v=v->prefer) v->loc=base+(++cnt);
		newseg+=base+cnt+1;
	}
}
int query(node *u,node *v){
	seg lsum,rsum;
	lsum.init();
	rsum.init();
	while(u->top!=v->top){
		if(u->top->depth>v->top->depth){
			lsum=query(u->a,u->top->loc-1,u->loc+1)+lsum;
			u=u->top->pa;
		}
		else{
			rsum=query(v->a,v->top->loc-1,v->loc+1)+rsum;
			v=v->top->pa;
		}
	}
	if(u->depth>v->depth)
		lsum=query(u->a,v->loc-1,u->loc+1)+lsum;
	else
		rsum=query(v->a,u->loc-1,v->loc+1)+rsum;
	lsum.reverse();
	return (lsum+rsum).ans();
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	V[1].pa=V;
	V[1].build();
	makechain(V+1,V+n+1);
	for(node *u=V+1;u<V+n+1;u++) u->a[u->loc].readmap();
	for(node *u=V+1;u<V+n+1;u++) if(u->size==1)
		for(int l=(u->top->loc-1)>>1,r=(u->loc+1)>>1;l^r^1;l>>=1,r>>=1)
			for(int i=l+1;i<r;i++) update(u->a,i);
	while(m--)
		switch(getchar()){
			case 'C':
				scanf("%d",&x);
				V[x].renew();
				break;
			case 'Q':
				scanf("%d%d",&x,&y);
				printf("%d\n",query(V+x,V+y));
				break;
			default: m++;
		}
}

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=3001,M=N*6,A=1001;
typedef int type;
const type Inf=100000000,inf=10000000;
int n,m;
struct node;
struct point;
struct edge{
	node *st,*ed; int w;
} E[M],*newE=E;
struct line{
	int w; node *right; point *ed; line *next; bool vis;
} L[M],*newL=L;
bool cmp(line*,line*);
struct point{
	int x,y; double a;
	line *son;
	bool vis;
	void work(){
		static line *tmp[M]; line **top=tmp;
		for(line *e=son;e;e=e->next){
			e->ed->a=atan2(e->ed->y-y,e->ed->x-x);
			*top++=e;
		}
		sort(tmp,top,cmp);
		son=*tmp;
		for(line **i=tmp+1;i<top;i++)
			(*(i-1))->next=*i;
		(*(top-1))->next=son;
	}
} P[N];
bool cmp(line *A,line *B){
	return A->ed->a<B->ed->a;
}
struct node{
	type in; node *pre,*belong; bool vis,ins;
} V[A],*newV=V;
type Directed_MST(node *root,node *begin,node *end,edge *ebegin,edge *eend){
	type ans=0;
	node *u,*v; edge *e;
	while(true){
		for(u=begin;u<end;u++) u->vis=false,u->in=Inf,u->belong=NULL;
		root->vis=true;
		root->in=0;
		for(e=ebegin;e<eend;e++) if(e->st!=e->ed&&e->ed->in>e->w){
			e->ed->in=e->w;
			e->ed->pre=e->st;
		}
		for(u=begin;u<end;u++)
			if(u->in==Inf) return inf-1;
			else ans+=u->in;
		node *number=begin;
		for(u=begin;u<end;u++){
			for(v=u;!v->vis;v=v->pre) v->vis=v->ins=true;
			if(v!=root&&v->ins){
				for(node *vv=v->pre;vv!=v;vv=vv->pre)
					vv->belong=number;
				v->belong=number++;
			}
			for(v=u;v->ins;v=v->pre) v->ins=false;
		}
		if(number==begin) return ans;
		for(u=begin;u<end;u++) if(!u->belong) u->belong=number++;
		for(e=ebegin;e<eend;e++) if(e->st!=e->ed){
			e->w-=e->ed->in;
			e->st=e->st->belong;
			e->ed=e->ed->belong;
		}
		root=root->belong;
		end=number;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&P[i].x,&P[i].y);
	for(int i=0;i<m;i++){
		static int x,y,v1,v2; scanf("%d%d%d%d",&x,&y,&v1,&v2);
		newL->ed=P+y; newL->w=v1; newL->next=P[x].son; P[x].son=newL++;
		newL->ed=P+x; newL->w=v2; newL->next=P[y].son; P[y].son=newL++;
	}
	for(int i=1;i<=n;i++) P[i].work();
	node *root=newV++;
	for(line *i=L;i<newL;i++) if(!i->vis){
		for(line *cur=i,*oppo;!cur->vis;cur=oppo->next){
			cur->vis=true;
			cur->right=newV;
			oppo=L+((cur-L)^1);
			if(oppo->right){
				if(cur->w)  *newE++=(edge){oppo->right,cur->right,cur->w};
				if(oppo->w) *newE++=(edge){cur->right,oppo->right,oppo->w};
			}
		}
		*newE++=(edge){root,newV++,inf};
	}
	printf("%d\n",Directed_MST(root,V,newV,E,newE)-inf);
}

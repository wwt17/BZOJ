#include <cstdio>
#include <queue>
#define INF 0x7FFFFFFF
#define data int
int N,M,i,j;struct node;
struct edge{
	edge *next; node* ed; data cap;
} E[720000],*Es=E;
struct node{
	edge* son; int depth,gout;
	node():son(NULL),gout(0){}
	inline void addedge(node* To,data C){
		*Es=(edge){son,To,C}; son=Es++;
	}
} *S=new node,*T=new node,plant[20][30];//define nodes
int Score[20][30];
inline void addedge(node* u,node* v,const int c1,const int c2){
	u->addedge(v,c1);
	v->addedge(u,c2);
}
#define addedge(u,v,c) addedge(u,v,c,0)
bool layered(){
	for(i=0;i<N;++i) for(j=0;j<M;++j) plant[i][j].depth=0;//clear
	T->depth=0;
	std::queue<node*> q; node *x,*y;
	for(q.push(S),S->depth=1;!q.empty();q.pop())
		for(edge* e=(x=q.front())->son;e;e=e->next)
			if(e->cap&&!(y=e->ed)->gout&&!y->depth){
				q.push(y),y->depth=x->depth+1;
				if(y==T) return true;
			}
	return false;
}
data flow(node* x,int F){
	if(x==T) return F;
	data left=F,Flow; node* y;
	for(edge* e=x->son;e&&left;e=e->next)
		if(e->cap&&!(y=e->ed)->gout&&x->depth+1==y->depth&&(Flow=flow(y,std::min(left,e->cap))))
			e->cap-=Flow,E[(e-E)^1].cap+=Flow,left-=Flow;
	if(!(F-=left)) x->depth=0;
	return F;
}
void Remove_Rings(){//toposort
	std::queue<node*> q;
	for(i=0;i<N;++i) for(j=0;j<M;++j) if(!plant[i][j].gout) q.push(&plant[i][j]);
	for(;!q.empty();q.pop())
		for(edge* e=q.front()->son;e;e=e->next)
			if(!e->cap&&!--e->ed->gout) q.push(e->ed);
}
int main(){
	//make graph
	scanf("%d%d",&N,&M);
	int w,r,c;
	for(i=0;i<N;++i) for(j=0;j<M;++j){
		scanf("%d",&Score[i][j]);
		if(j) addedge(&plant[i][j-1],&plant[i][j],INF),++plant[i][j-1].gout;
		for(scanf("%d",&w);w;--w){
			scanf("%d%d",&r,&c);
			addedge(&plant[r][c],&plant[i][j],INF),++plant[r][c].gout;
		}
	}
	Remove_Rings();
	data Ans=0,Flow;
	for(i=0;i<N;++i) for(j=0;j<M;++j)
		if(Score[i][j]>0){
			addedge(S,&plant[i][j],Score[i][j]);
			if(!plant[i][j].gout) Ans+=Score[i][j];
		}else
			addedge(&plant[i][j],T,-Score[i][j]);
	//calc flow
	while(layered())
		while(Flow=flow(S,INF))
			Ans-=Flow;
	printf("%d\n",Ans);
}

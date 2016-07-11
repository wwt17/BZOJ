#include <cstdio>
#include <queue>
#define inf 0x7FFFFFFF
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node *pre,*ed; edge* next; int cap,cost;
} E[128500],*Es=E;
struct node{
	edge* son; int dist,flow; edge* fro;
	node():son(NULL){}
};
inline void addedge(node* u,node* v,const int cap,const int cost){
	*Es=(edge){u,v,u->son,cap,cost},u->son=Es++;
	*Es=(edge){v,u,v->son,0,-cost},v->son=Es++;
}
//define graph
node *S,*T,worker[251],product[251];
bool Aij; int m,n,i,j,k,Ci,Si,Ti[7],Wij;
int main(){
	//make graph
	scanf("%d%d",&m,&n);
	S=new node,T=new node;
	for (i=1;i<=n;++i){scanf("%d",&Ci);addedge(product+i,T,Ci,0);}
	for (i=1;i<=m;++i) for (j=1;j<=n;++j)
		{scanf("%d",&Aij);if (Aij) addedge(worker+i,product+j,inf,0);}
	for (i=1;i<=m;++i){
		scanf("%d",&Si);
		for (j=1;j<=Si;++j) scanf("%d",&Ti[j]); Ti[j]=inf;
		for (j=1;j<=Si+1;++j)
			{scanf("%d",&Wij);addedge(S,worker+i,Ti[j]-Ti[j-1],Wij);}
	}
	//calc cost flow
	long long Ans=0; 
	for(;;){
		std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for (i=1;i<=m;++i) worker[i].dist=inf;
		for (i=1;i<=n;++i) product[i].dist=inf;
		S->dist=0;S->fro=NULL;T->dist=inf;
		for (q.push(S);!q.empty();q.pop())
			for (e=(x=q.front())->son;e;e=e->next)
				if (e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					{y->fro=e;if(y->dist<T->dist)q.push(y);}
		if (T->dist==inf) break;
		int c=inf;
		for (e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for (e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%I64d\n",Ans);
}

#include <cstdio>
#include <queue>
#define INF 0x7FFFFFFF
inline bool mini(int &a,const int b){return a>b?(a=b,true):false;}
struct node;
struct edge{
	node *pre,*ed; edge* next; int cap,cost;
} E[15*15*12],*Es=E;
struct node{
	edge* son; int dist,flow; edge* fro; bool inq;
	node():son(NULL){}
};
inline void addedge(node* u,node* v,const int cap,const int cost){
	*Es=(edge){u,v,u->son,cap,cost},u->son=Es++;
	*Es=(edge){v,u,v->son,0,-cost},v->son=Es++;
}
//define graph
node *S,*T,V[15][15][2];
const int dir[4][2]={ 0,-1, 0,1, -1,0, 1,0 };
const char dirname[4]={ 'L', 'R', 'U', 'D' };
int main(){
	//make graph
	int R,C,r,c;
	scanf("%u%u\n",&R,&C);
	S=new node,T=new node;
	for(r=0;r<R;scanf("\n"),++r)
		for(c=0;c<C;++c){
			addedge(S,V[r][c],1,0);
			addedge(V[r][c]+1,T,1,0);
			char ch=getchar();
			for(int d=0;d<4;++d)
				addedge(V[r][c],V[(r+dir[d][0]+R)%R][(c+dir[d][1]+C)%C]+1,1,ch!=dirname[d]);
		}
	//calc cost flow
	int Ans=0;
	for(;;){
		static std::queue<node*> q; node *x,*y; edge *e;
		//clear
		for(r=0;r<R;++r) for(c=0;c<C;++c) V[r][c][0].dist=V[r][c][1].dist=INF;
		T->dist=INF;
		S->dist=0;S->fro=NULL;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),x->inq=false)
			for(e=(x=q.front())->son;e;e=e->next)
				if(e->cap&&mini((y=e->ed)->dist,x->dist+e->cost))
					{ y->fro=e; if(!y->inq&&y->dist<T->dist) q.push(y),y->inq=true; }
		if(T->dist==INF) break;
		int c=INF;
		for(e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for(e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c;
		Ans+=T->dist;
	}
	//print Ans
	printf("%d\n",Ans);
}

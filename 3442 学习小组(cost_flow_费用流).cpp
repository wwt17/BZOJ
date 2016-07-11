#include <cstdio>
#include <queue>
const int inf=0x7FFFFFFF,N=105,M=N*N*2;
inline bool mini(int &a,const int b){
	return a>b?(a=b,true):false;
}
int n,m,k;
struct node;
struct edge{
	node *pre,*ed; edge *next; int cap,cost;
} E[M<<1],*newE=E;
struct node{
	edge *son; int dist,flow; edge *fro; bool inq;
	node():son(NULL){}
} S[2],*T=S+1,student[N],group[N];
inline void addedge(node *u,node *v,const int cap,const int cost){
	*newE=(edge){u,v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){v,u,v->son,0,-cost},v->son=newE++;
}
int c[N],f[N],cnt[N];
int main(){
	//make graph
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++) scanf("%d",c+i);
	for(int i=1;i<=m;i++) scanf("%d",f+i);
	for(int i=1;i<=n;i++){
		addedge(S,student+i,k,0);
		addedge(student+i,T,k-1,0);
		char s[N]; scanf("%s",s+1);
		for(int j=1;j<=m;j++) if(s[j]=='1'){
			addedge(student+i,group+j,1,-f[j]);
			addedge(group+j,T,1,c[j]*(cnt[j]*2+1));
			cnt[j]++;
		}
	}
	int Ans=0;
	for(;;){
		std::queue<node*> q; node *u,*v; edge *e;
		//clear
		for(int i=1;i<=n;i++) student[i].dist=inf;
		for(int j=1;j<=m;j++) group[j].dist=inf;
		S->dist=0;S->fro=NULL; T->dist=inf;
		for(q.push(S),S->inq=true;!q.empty();q.pop(),u->inq=false)
			for(e=(u=q.front())->son;e;e=e->next)
				if(e->cap&&mini((v=e->ed)->dist,u->dist+e->cost))
					{ v->fro=e; if(!v->inq) q.push(v),v->inq=true; }
		if(T->dist==inf) break;
		int c=inf;
		for(e=T->fro;e;e=e->pre->fro) mini(c,e->cap);
		for(e=T->fro;e;e=e->pre->fro) e->cap-=c,E[(e-E)^1].cap+=c,Ans+=c*e->cost;
	}
	//print Ans
	printf("%d\n",Ans);
}

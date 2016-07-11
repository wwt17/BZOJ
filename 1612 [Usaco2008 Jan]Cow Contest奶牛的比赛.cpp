#include <cstdio>
struct node;
struct edge{
	node* ed; edge* next;
	edge(node* _ed,edge* _next):ed(_ed),next(_next){}
};
struct node{
	edge* son; int cnt; bool vis;
	void addedge(node* ed){
		son=new edge(ed,son);
	}
	void DFS();
} V[101];
void node::DFS(){
	if(vis) return;
	vis=true; ++cnt;
	for(edge* e=son;e;e=e->next)
			e->ed->DFS();
}
int main(){
	int N,M,u,v;
	scanf("%d%d",&N,&M);
	while(M--){
		scanf("%d%d",&u,&v);
		V[u].addedge(V+v);
	}
	for(u=1;u<=N;++u){
		V[u].DFS();
		for(v=1;v<=N;++v) if(V[v].vis){
			++V[u].cnt;
			V[v].vis=false;
		}
	}
	int Ans=0;
	for(u=1;u<=N;++u) if(V[u].cnt==N+1)
		++Ans;
	printf("%d\n",Ans);
}

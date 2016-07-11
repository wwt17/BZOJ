#include <cstdio>
#include <algorithm>
using namespace std;
#define inf 0x7FFFFFFF
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
int N,M,Ui,Vi,Ki,cnt,cnt2; long long sum;
struct node;
struct edge{
	node *pre,*ed; edge *next; int w;
	inline bool link();
} E[2000000],*newE=E,*topE=E;
struct node{
	edge *son; int h; bool vis; node* belong;
	node():belong(this){}
	void correct(){
		if(belong==this) return;
		belong->correct();
		belong=belong->belong;
	}
	void DFS(){
		if(vis) return; vis=true;
		for(edge* e=son;e;e=e->next)
			e->ed->DFS();
	}
} V[100001],*u,*v;
inline bool cmp(const edge &a,const edge &b){
	return a.ed->h>b.ed->h || a.ed->h==b.ed->h && a.w<b.w;
}
inline bool edge::link(){
	pre->correct(); ed->correct();
	if(pre->belong==ed->belong) return false;
	ed->belong->belong=pre->belong;
	return true;
}
int main(){
	read(N),read(M);
	for(int i=1;i<=N;i++) read(V[i].h);
	while(M--){
		read(Ui),read(Vi),read(Ki);
		u=V+Ui,v=V+Vi;
		if(u->h>=v->h) *newE=(edge){u,v,u->son,Ki},u->son=newE++;
		if(u->h<=v->h) *newE=(edge){v,u,v->son,Ki},v->son=newE++;
	}
	V[1].DFS();
	for(int i=1;i<=N;i++) if(V[i].vis) cnt++;
	for(edge* e=E;e<newE;e++) if(e->pre->vis)
		if(e!=topE) *topE++=*e; else topE++;
	sort(E,topE,cmp);
	cnt2=cnt-1;
	for(edge* e=E;e<topE;e++) if(e->link()){
		sum+=e->w;
		if(!--cnt2) break;
	}
	printf("%u %llu\n",cnt,sum);
}

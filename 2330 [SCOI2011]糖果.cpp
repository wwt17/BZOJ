#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
#define sizeN 100001
#define inf 0x7fffffff
struct node;
struct edge{
	node* ed; edge* next; int w;
} E[200000],*newedge=E;
struct node{
	edge* son; int dist,sum; bool inq;
	void addedge(node* ed,const int w){
		newedge->ed=ed;
		newedge->next=son;
		newedge->w=w;
		son=newedge++;
	}
} V[sizeN];
inline bool maxi(int &a,const int b){return a<b?(a=b,true):false;}
int N,K,X,A,B,i; long long ans;
int main(){
	#define NoAnswer() { puts("-1"); exit(0); }
	scanf("%u%u",&N,&K);
	while(K--)
		switch(scanf("%u%u%u",&X,&A,&B),X){
			case 1:
				V[A].addedge(V+B,0);
				V[B].addedge(V+A,0);
				break;
			case 4: swap(A,B);
			case 2:
				if(A==B) NoAnswer();
				V[A].addedge(V+B,1);
				break;
			case 3: swap(A,B);
			case 5:
				V[A].addedge(V+B,0);
		}
	//SPFA
	queue<node*> q; node *u,*v; edge *e;
	for(v=V+1;v<=V+N;++v) q.push(v),v->inq=true,v->dist=1;
	for(;!q.empty();u->inq=0,q.pop())
		for(e=(u=q.front())->son;e;e=e->next)
			if(maxi((v=e->ed)->dist,u->dist+e->w)&&!v->inq){
				if(v->sum++>=N) NoAnswer();
				q.push(v),v->inq=1;
			}
	for (i=1;i<=N;++i) ans+=V[i].dist;
	printf("%llu\n",ans);
}

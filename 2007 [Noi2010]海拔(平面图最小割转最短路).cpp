#include <cstdio>
#include <algorithm>
using namespace std;

const int N=505,M=N*N*4;
typedef long long ll;
ll inf=(ll)1e6*M;

inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}

int n;

struct node;
struct edge{
	node *ed;
	edge *next;
	ll w;
} E[M],*newE=E;
struct node{
	edge *son;
	ll dist;
	int inh;
} S[2],*T=S+1,V[N][N];

void addedge(node *u,node *v,ll w){
	*newE=(edge){v,u->son,w},u->son=newE++;
}

node *h[N*N];
int size;

void swaph(int &i,int j){
	node *t=h[i]; h[i]=h[j]; h[j]=t;
	h[i]->inh=i;
	h[j]->inh=j;
	i=j;
}
void up(int i){
	int j;
	while(j=i>>1){
		if(h[i]->dist<h[j]->dist)
			swaph(i,j);
		else
			break;
	}
}
void down(int i){
	int j;
	while((j=i<<1)<=size){
		if((j|1)<=size&&h[j|1]->dist<h[j]->dist) j|=1;
		if(h[j]->dist<h[i]->dist)
			swaph(i,j);
		else
			break;
	}
}
void push(node *u){
	h[u->inh=++size]=u;
	up(size);
}
void pop(){
	h[1]->inh=0;
	if(size>1){
		h[1]=h[size--];
		h[1]->inh=1;
		down(1);
	}
	else
		size--;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		for(int j=0;j<n;j++)
			addedge(i==n?S:&V[i][j],i==0?T:&V[i-1][j],getint());
	for(int i=0;i<n;i++)
		for(int j=0;j<=n;j++)
			addedge(j==0?S:&V[i][j-1],j==n?T:&V[i][j],getint());
	for(int i=0;i<=n;i++)
		for(int j=0;j<n;j++)
			addedge(i==0?T:&V[i-1][j],i==n?S:&V[i][j],getint());
	for(int i=0;i<n;i++)
		for(int j=0;j<=n;j++)
			addedge(j==n?T:&V[i][j],j==0?S:&V[i][j-1],getint());
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			V[i][j].dist=inf;
	T->dist=inf;
	S->dist=0;
	push(S);
	while(size){
		node *u=h[1]; pop();
		if(u==T) break;
		for(edge *e=u->son;e;e=e->next){
			node *v=e->ed;
			if(u->dist+e->w<v->dist){
				v->dist=u->dist+e->w;
				if(v->inh)
					up(v->inh);
				else
					push(v);
			}
		}
	}
	printf("%lld\n",T->dist);
}

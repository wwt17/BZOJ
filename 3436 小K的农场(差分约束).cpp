#include <cstdio>
const int N=10005,M=10005,inf=1000000000;
int n,m;
struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[M<<1],*newE=E;
struct node{
	edge *son; int dist,cnt; bool inq;
} V[N],*s[N],**top=s;
void addedge(node *u,node *v,int w){
	*newE=(edge){v,u->son,w},u->son=newE++;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int t,a,b,c;
		scanf("%d",&t);
		switch(t){
			case 1:
				scanf("%d%d%d",&a,&b,&c);
				addedge(V+a,V+b,-c);
				break;
			case 2:
				scanf("%d%d%d",&a,&b,&c);
				addedge(V+b,V+a,c);
				break;
			case 3:
				scanf("%d%d",&a,&b);
				addedge(V+a,V+b,0);
				addedge(V+b,V+a,0);
				break;
		}
	}
	for(int i=1;i<=n;i++) V[i].dist=inf,*top++=V+i,V[i].inq=true;
	while(s<top){
		node *u=*--top; u->inq=false;
		if(u->dist==inf) u->dist=0;
		for(edge *e=u->son;e;e=e->next){
			node *v=e->ed;
			if(u->dist+e->w<v->dist){
				v->dist=u->dist+e->w;
				if(!v->inq){
					v->inq=true;
					if(++v->cnt>n){
						puts("No");
						return 0;
					}
					*top++=v;
				}
			}
		}
	}
	puts("Yes");
}

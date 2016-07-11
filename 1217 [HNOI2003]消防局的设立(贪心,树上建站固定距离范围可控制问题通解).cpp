#include <cstdio>
#include <algorithm>
using namespace std;
const int N=10005,d=2;
int n;
struct node{
	node *son,*next,*pa;
	int f,g;
} V[N],*q[N],**head=q,**tail=q;
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		static int x; scanf("%d",&x);
		V[i].pa=V+x;
		V[i].next=V[x].son;
		V[x].son=V+i;
	}
	*tail++=V+1;
	while(head<tail){
		node *u=*head++;
		for(node *v=u->son;v;v=v->next)
			*tail++=v;
	}
	int cnt=0;
	for(int i=1;i<=n;i++) V[i].f=-1;
	while(tail>q+1){
		node *v=*--tail,*u=v->pa;
		if(v->g==d){
			cnt++;
			v->f=d;
		}
		if(v->f>=v->g)
			v->g=-1;
		u->f=max(u->f,v->f-1);
		u->g=max(u->g,v->g+1);
	}
	if(V[1].f>=V[1].g) V[1].g=-1;
	if(V[1].g>-1) cnt++;
	printf("%d\n",cnt);
}

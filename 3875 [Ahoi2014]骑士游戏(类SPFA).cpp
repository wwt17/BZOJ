#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=(int)2e5+5,M=(int)1e6+5;
const ll inf=(ll)1e18;

int n;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M],*newE=E;
struct node{
	edge *son;
	int cnt;
	ll nor,spe,val,tmp;
	bool inq;
	bool renew(){
		tmp=min(tmp,min(cnt?inf:nor,spe));
		return tmp<val;
	}
} V[N],*q[N];
int head,tail;

int main(){
	scanf("%d",&n);
	for(node *u=V+1;u<=V+n;u++){
		scanf("%lld%lld%d",&u->nor,&u->spe,&u->cnt);
		for(int i=0;i<u->cnt;i++){
			int x; scanf("%d",&x); node *v=V+x;
			*newE=(edge){u,v->son},v->son=newE++;
		}
		u->val=inf;
		u->tmp=u->spe;
		q[tail++]=u; u->inq=true;
	}
	while(head!=tail){
		node *u=q[head]; if(++head==N) head=0; u->inq=false;
		ll d=u->val-u->tmp;
		u->val=u->tmp;
		for(edge *e=u->son;e;e=e->next){
			node *v=e->ed;
			if(d>inf/2){
				v->cnt--;
				v->nor+=u->val;
			}
			else{
				v->nor-=d;
			}
			if(v->renew()&&!v->inq){
				v->inq=true; q[tail]=v; if(++tail==N) tail=0;
			}
		}
	}
	printf("%lld\n",V[1].val);
}

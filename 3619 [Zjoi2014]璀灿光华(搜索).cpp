#include <cstdio>
using namespace std;

typedef long long ll;
const int N=75;
char c;
inline int getint(){
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}

int n,n3;
struct node{
	int g; int cnt;
	node *next[6],*nxt[6];
	bool flag,done;
	int c;
} V[N*N*N];
node *q[N*N*N];
int dir=0;
void bfs(node *s){
	#define push_back(v) (*tail++=v)
	node **head=q,**tail=q;
	for(node *u=V;u<V+n3;u++) u->flag=false;
	s->flag=true;
	s->done=true;
	push_back(s);
	for(node **it=head;it!=tail;it++){
		node *u=*it;
		for(int j=0;j<u->cnt;j++){
			node *v=u->next[j];
			if(v&&!v->flag&&v->cnt==5){
				v->flag=true;
				v->done=true;
				push_back(v);
			}
		}
	}
	for(node *u=V;u<V+n3;u++) if(u->cnt==4){
		for(int j=0;j<u->cnt;j++) if(u->next[j]&&u->next[j]->flag){
			u->flag=true;
			push_back(u);
			break;
		}
	}
	for(node *u=V;u<V+n3;u++) if(u->cnt==3){
		for(int j=0;j<u->cnt;j++) if(u->next[j]&&u->next[j]->flag){
			u->flag=true;
			push_back(u);
			break;
		}
	}
	while(head<tail){
		node *u=*head++;
		for(int j=0;j<u->cnt;j++){
			node *v=u->next[j];
			if(v&&!v->flag){
				v->flag=true;
				u->nxt[dir]=v;
				push_back(v);
			}
		}
	}
	dir++;
}

node *seq[100];
int tot;
ll ans,amax=0,amin=ll(1e16);
void search(int now){
	if(now==tot){
		if(ans>amax) amax=ans;
		if(ans<amin) amin=ans;
		return;
	}
	for(int j=0;j<6;j++){
		for(node *v=seq[now];v;v=v->nxt[j])
			if(!v->c++) ans+=v->g;
		search(now+1);
		for(node *v=seq[now];v;v=v->nxt[j])
			if(!--v->c) ans-=v->g;
	}
}
int main(){
	n=getint();
	n3=n*n*n;
	for(node *u=V;u<V+n3;u++){
		u->g=getint();
		for(;c!='\n'&&c!='\r';){
			int y=getint();
			if(y){
				u->next[u->cnt]=(y?V+y-1:NULL);
				u->cnt++;
			}
		}
	}
	if(n==2){
		return 0;
	}
	for(int i=0;i<n3;i++) if(V[i].cnt==5&&!V[i].done){
		bfs(V+i);
	}
	for(node *u=V;u<V+n3;u++){
		if(u->g==0){
			seq[tot++]=u;
		}
	}
	search(0);
	printf("%lld %lld\n",amin,amax);
}

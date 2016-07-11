/*
VFK的cha人数据：
in:
4 7 2
1 2 1
2 4 1
2 3 1
3 1 1
4 2 1
1 3 100
3 4 100
1 2
out:
200
102
*/
#include <cstdio>
#include <queue>
using namespace std;

const int N=100005,M=200005,inf=(int)2e9+7;

int n,m,l;
struct node;
struct edge{
	node *u,*v;
	edge *next;
	int c;
	bool ban;
	void read();
} E[M],*tmp[M];
struct node{
	edge *son;
	int dist,pre,suf,val;
	bool inq;
	int lab;
	node *occ;
} V[N],*seq[N];

void edge::read(){
	int x,y; scanf("%d%d%d",&x,&y,&c);
	u=V+x;
	v=V+y;
	next=u->son;
	u->son=this;
}

struct data{
	int lab,dis;
};
bool operator < (const data &a,const data &b){
	return a.dis>b.dis;
}

priority_queue<data> h;

void spfa(node *s){
	static queue<node*> q;
	static node* stack[N];
	int top=0;
	s->dist=s->pre;
	s->inq=true;
	q.push(s);
	while(!q.empty()){
		node *u=q.front(); q.pop(); u->inq=false;
		for(edge *e=u->son;e;e=e->next) if(!e->ban){
			node *v=e->v;
			int d=u->dist+e->c;
			if(v->lab>s->lab){
				if(v->occ!=s){
					stack[top++]=v;
					v->occ=s;
					v->val=d+v->suf;
				}
				else{
					v->val=min(v->val,d+v->suf);
				}
			}
			else
			if(d<v->dist){
				v->dist=d;
				if(!v->inq){
					v->inq=true;
					q.push(v);
				}
			}
		}
	}
	while(top--){
		node *u=stack[top];
		h.push((data){u->lab,u->val});
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=m;i++) E[i].read();
	for(int i=1;i<=l;i++){
		int x; scanf("%d",&x);
		tmp[i]=E+x;
		seq[i-1]=tmp[i]->u;
		seq[i]=tmp[i]->v;
	}
	for(int i=0;i<=l;i++) seq[i]->lab=i;
	seq[0]->pre=0;
	for(int i=1;i<=l;i++) seq[i]->pre=seq[i-1]->pre+tmp[i]->c;
	seq[l]->suf=0;
	for(int i=l-1;i>=0;i--) seq[i]->suf=seq[i+1]->suf+tmp[i+1]->c;
	for(int i=1;i<=n;i++) V[i].dist=inf;
	for(int i=1;i<=l;i++){
		tmp[i]->ban=true;
		node *u=seq[i-1];
		spfa(u);
		printf("%d\n",h.empty()?-1:h.top().dis);
		while(!h.empty()&&h.top().lab<=i)
			h.pop();
		tmp[i]->ban=false;
	}
}

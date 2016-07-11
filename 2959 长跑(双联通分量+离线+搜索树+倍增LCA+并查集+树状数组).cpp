#include <cstdio>
const int N=(int)1.5e5+5,M=N*5,logN=18;
int n,m,t[N];
void add(int x,int d){
	for(;x;x-=x&-x) t[x]+=d;
}
int query(int x){
	int s=0;
	for(;x<=n;x+=x&-x) s+=t[x];
	return s;
}
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *belong,*top,*pa[logN];
	int depth,a,s,st,en;
	node *get(){
		return belong?(belong=belong->get()):this;
	}
	node *got(){
		return top==this?this:(top=top->got());
	}
	void modify(int val){
		add(st,s-val);
		add(en,val-s);
		s=val;
	}
	void dfs(){
		static int len=0;
		st=len;
		for(int j=1;j<logN;j++) pa[j]=pa[j-1]->pa[j-1];
		for(edge *e=son;e;e=e->next) if(e->ed!=pa[0]){
			e->ed->depth=depth+1;
			e->ed->pa[0]=this;
			e->ed->dfs();
		}
		en=++len;
		modify(a);
	}
} V[N];
node *lca(node *u,node *v){
	for(int j=logN-1;j>=0;j--) if(u->pa[j]->depth>=v->depth) u=u->pa[j];
	for(int j=logN-1;j>=0;j--) if(v->pa[j]->depth>=u->depth) v=v->pa[j];
	for(int j=logN-1;j>=0;j--) if(u->pa[j]!=v->pa[j]) u=u->pa[j],v=v->pa[j];
	return u==v?u:u->pa[0];
}
struct data{
	int type,val;
	node *u,*v;
	void read(){
		int x,y;
		scanf("%d%d%d",&type,&x,&y);
		if(type==2){
			u=V+x;
			val=y;
			return;
		}
		u=V+x;
		v=V+y;
		if(type==1&&u->get()!=v->get()){
			*newE=(edge){v,u->son},u->son=newE++;
			*newE=(edge){u,v->son},v->son=newE++;
			u->get()->belong=v->get();
		}
	}
	void work(){
		if(type==1){
			if(u->get()!=v->get())
				v->get()->belong=u->get();
			else{
				node *w=lca(u,v)->got();
				for(u=u->got();u!=w;u=u->pa[0]->got()){
					w->modify(w->s+u->s);
					u->modify(0);
					u->top=w;
				}
				for(v=v->got();v!=w;v=v->pa[0]->got()){
					w->modify(w->s+v->s);
					v->modify(0);
					v->top=w;
				}
			}
		}
		else
		if(type==2){
			node *w=u->got();
			w->modify(w->s+val-u->a);
			u->a=val;
		}
		else
		if(type==3){
			if(u->get()!=v->get()){
				puts("-1");
				return;
			}
			node *w=lca(u,v)->got();
			u=u->got();
			v=v->got();
			printf("%d\n",query(u->en)+query(v->en)-query(w->en)*2+w->s);
		}
	}
} seq[M];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].a);
	for(int i=0;i<m;i++) seq[i].read();
	for(int i=1;i<=n;i++) V[i].belong=NULL,V[i].top=V+i;
	for(int i=1;i<=n;i++) if(!V[i].depth){
		V[i].depth=1;
		V[i].pa[0]=V+i;
		V[i].dfs();
	}
	for(int i=0;i<m;i++) seq[i].work();
}

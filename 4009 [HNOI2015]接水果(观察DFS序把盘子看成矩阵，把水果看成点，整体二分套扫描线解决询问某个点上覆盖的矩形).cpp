#include <cstdio>
#include <algorithm>
using namespace std;

const int N=40005,P=N,Q=N,logN=16;

int n,p,q;

int getint(){
	bool f=false;
	char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return f?-a:a;
}

int len;
int t[N];
void add(int x,int d){
	for(;x<=len;x+=x&-x) t[x]+=d;
}
int query(int x){
	int s=0; for(;x;x-=x&-x) s+=t[x]; return s;
}

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	node *fa[logN];
	edge *son;
	int depth;
	int st,en;
	void dfs(){
		for(int i=1;i<logN;i++) fa[i]=fa[i-1]->fa[i-1];
		st=len;
		for(edge *e=son;e;e=e->next) if(e->ed!=fa[0]){
			e->ed->fa[0]=this;
			e->ed->depth=depth+1;
			e->ed->dfs();
		}
		en=++len;
	}
} V[N];

node* LCA(node *u,node *v){
	if(u->depth>v->depth){
		for(int j=logN-1;j>=0;j--) if(u->fa[j]->depth>=v->depth) u=u->fa[j];
	}
	else{
		for(int j=logN-1;j>=0;j--) if(v->fa[j]->depth>=u->depth) v=v->fa[j];
	}
	if(u==v) return u;
	for(int j=logN-1;j>=0;j--) if(u->fa[j]!=v->fa[j]) u=u->fa[j],v=v->fa[j];
	return u->fa[0];
}

bool contain(node *u,node *v){
	return u->st<=v->st&&v->en<=u->en;
}

struct seg{
	int x,y1,y2;
	int w;
	friend bool operator < (const seg &a,const seg &b){
		return a.x<b.x;
	}
	void work(){
		add(y1+1,+w);
		add(y2+1,-w);
	}
} seq[P*2*2],*newseg=seq;

struct rect{
	int x1,x2,y1,y2;
	void work(){
		*newseg++=(seg){x1,y1,y2,+1};
		*newseg++=(seg){x2,y1,y2,-1};
	}
};

struct plate{
	node *u,*v,*lca; int w;
	int cntrect;
	rect r[2];
	friend bool operator < (const plate &a,const plate &b){
		return a.w<b.w;
	}
	void init(){
		u=V+getint();
		v=V+getint();
		w=getint();
		lca=LCA(u,v);
		if(u==lca) swap(u,v);
		if(v==lca){
			cntrect=2;
			for(edge *e=v->son;e;e=e->next) if(e->ed!=v->fa[0]){
				node *t=e->ed;
				if(contain(t,u)){
					r[0]=(rect){0,t->st,u->st,u->en};
					r[1]=(rect){u->st,u->en,t->en,len};
					break;
				}
			}
		}
		else{
			cntrect=1;
			if(u->en>v->en) swap(u,v);
			r[0]=(rect){u->st,u->en,v->st,v->en};
		}
	}
	void work(){
		for(int c=0;c<cntrect;c++)
			r[c].work();
	}
} plt[P];

int ans[Q];

struct fruit{
	node *u,*v;
	int k,id,res;
	void init(int ID){
		u=V+getint();
		v=V+getint();
		k=getint();
		id=ID;
		if(u->en>v->en) swap(u,v);
	}
	friend bool operator < (const fruit &a,const fruit &b){
		return a.u->en<b.u->en;
	}
} frt[Q];

bool cmp(const fruit &a,const fruit &b){
	return (a.k>a.res)<(b.k>b.res);
}

void work(plate *pbeg,plate *pend,fruit *fbeg,fruit *fend){
	if(fend-fbeg==0) return;
	if(pend-pbeg==1){
		for(fruit *f=fbeg;f<fend;f++){
			ans[f->id]=pbeg->w;
		}
		return;
	}
	plate *pmid=pbeg+(pend-pbeg>>1);
	newseg=seq;
	for(plate *p=pbeg;p<pmid;p++) p->work();
	sort(seq,newseg);
	sort(fbeg,fend);
	seg *s=seq;
	fruit *fmid=fbeg;
	for(fruit *f=fbeg;f<fend;f++){
		for(;s<newseg&&s->x<f->u->en;s++)
			s->work();
		f->res=query(f->v->en);
		fmid+=(f->k<=f->res);
	}
	for(;s<newseg;s++) s->work();
	nth_element(fbeg,fmid,fend,cmp);
	for(fruit *f=fmid;f<fend;f++){
		f->k-=f->res;
	}
	work(pbeg,pmid,fbeg,fmid);
	work(pmid,pend,fmid,fend);
}

int main(){
	n=getint(),p=getint(),q=getint();
	for(int i=1;i<n;i++){
		int x=getint(),y=getint();
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	*newE=(edge){V+1,V[0].son},V[0].son=newE++;
	*newE=(edge){V+0,V[1].son},V[1].son=newE++;
	V->fa[0]=V;
	V->dfs();
	for(int i=0;i<p;i++) plt[i].init();
	sort(plt,plt+p);
	for(int i=0;i<q;i++) frt[i].init(i);
	work(plt,plt+p,frt,frt+q);
	for(int i=0;i<q;i++) printf("%d\n",ans[i]);
}

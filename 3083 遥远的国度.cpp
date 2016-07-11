#include <cstdio>
#include <cstring>
#define MAXN 100000
#define TSIZE 231100
#define INF 0x7FFFFFFF
inline int min(const int a,const int b){return a<b?a:b;}
inline void mini(int &a,const int b){if(a>b)a=b;}
using namespace std;
namespace ReadNum{
	/*
	本 namespace 仅适用于文件读入 unsigned int 类型
	使用时请在打开文件(stdin)后调用 initRead()
	*/
	#define BUFSIZE 100000
	char buf[2*BUFSIZE+32],*ch;
	inline void initRead(){
		fread(buf,1,BUFSIZE,stdin);
		fread(buf+BUFSIZE,1,BUFSIZE,stdin);
		ch=buf;
	}
	inline void read(int &x){
		x=0;
		while(*ch<'0'||*ch>'9') ++ch;
		while(*ch>='0'&&*ch<='9') x=x*10+*ch-48,++ch;
		if(ch>=buf+BUFSIZE){
			memcpy(buf,buf+BUFSIZE,BUFSIZE);
			fread(buf+BUFSIZE,1,BUFSIZE,stdin);
			ch-=BUFSIZE;
		}
	}
}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
namespace PrintNum{
	/*
	本 namespace 仅适用于文件输出 unsigned int 类型
	使用时请在输出结束后调用 endPrint()
	*/
	#define BUFSIZE 100000
	char buf[BUFSIZE+32],*ch=buf,tmp[10];
	inline void initPrint(){
		ch=buf;
	}
	inline void endPrint(){
		fwrite(buf,1,ch-buf,stdout);
		ch=buf;
	}
	//#define putC(c) (*ch++=c)
	inline void putC(const char c){*ch++=c;}
	inline void print(int x){
		char *t=tmp; if(!x) *t++='0';
		while(x) *t++=x%10+48,x/=10;
		while(t--!=tmp) *ch++=*t;
		if(ch>buf+BUFSIZE){
			fwrite(buf,1,ch-buf,stdout);
			ch=buf;
		}
	}
}
#define writeln(a) print(a),putC('\n')
using namespace ReadNum;
using namespace PrintNum;

int N,Base,newt;
struct tType{
	int Min,Cov;
} t[TSIZE];
#define cover(i,w) t[i].Min=t[i].Cov=w
#define update(i) t[i].Min=min(t[i<<1].Min,t[i<<1^1].Min)
#define down(i) t[i].Cov?(cover(i<<1,t[i].Cov),cover(i<<1^1,t[i].Cov),t[i].Cov=0):0
void correct(int i){
	if(i>>=1) correct(i),down(i);
}
void Modify(int l,int r,const int w){
	for(correct(--l),correct(++r);l^r^1;l>>=1,update(l),r>>=1,update(r)){
		if(!(l&1)) cover(l^1,w);
		if(  r&1 ) cover(r^1,w);
	}
	while(l>>=1) update(l);
}
int Query(int l,int r){
	int ans=INF;
	for(correct(--l),correct(++r);l^r^1;l>>=1,r>>=1){
		if(!(l&1)) mini(ans,t[l^1].Min);
		if(  r&1 ) mini(ans,t[r^1].Min);
	}
	return ans;
}
struct node *capital;
struct edge{
	node *ed; edge *next;
} E[MAXN<<1],*newedge=E;
struct node{
	edge *he; node *pa,*son,*next,*prefer,*top; int size,dep,lt,rt,w;
	void addedge(node* ed){
		*newedge=(edge){ed,he}; he=newedge++;
	}
	void BuildTree(){
		node *v; int maxsize=0;
		size=1;
		for(edge *e=he;e;e=e->next) if((v=e->ed)!=pa){
			v->pa=this;
			v->next=son;
			son=v;
			v->dep=dep+1;
			v->BuildTree();
			size+=v->size;
			if(maxsize<v->size) maxsize=v->size,prefer=v;
		}
	}
	void MakeChain(){
		lt=newt++; cover(lt,w);
		top=pa->prefer==this?pa->top:this;
		if(prefer) prefer->MakeChain();
		for(node *v=son;v;v=v->next) if(v!=prefer)
			v->MakeChain();
		rt=newt;
	}
	bool contains(node* y){ return lt<=y->lt&&y->rt<=rt; }
	int Query();
} V[MAXN+1];
void lineModify(node* x,node* y,const int w){
	if(x->top==y->top) return Modify(y->lt,x->lt,w);
	Modify(x->top->lt,x->lt,w);
	while(x=x->top->pa,x->top!=y->top)
		Modify(x->top->lt,x->lt,w);
	Modify(y->lt,x->lt,w);
}
node* LCA(node* a,node* b){
	while(a->top!=b->top)
		if(a->top->dep>b->top->dep)
		     a=a->top->pa;
		else b=b->top->pa;
	return a->dep<b->dep?a:b;
}
void Modify(node* u,node* v,int w){
	node* lca=LCA(u,v);
	lineModify(u,lca,w);
	lineModify(v,lca,w);
}
int node::Query(){
	if(this==capital) return ::Query(Base+1,newt-1);
	int ans=::Query(lt,lt);
	for(node* v=son;v;v=v->next)
		if(v->contains(capital))
			mini(ans,min(::Query(Base+1,lt-1),::Query(rt,newt-1)));
		else
			mini(ans,::Query(v->lt,v->rt-1));
	return ans;
}
int main(){
	initRead();
	int m,i,u,v,w,id,opt;
	read2(N,m);
	for(i=1;i<N;++i){
		read2(u,v);
		V[u].addedge(V+v);
		V[v].addedge(V+u);
	}
	for(i=1;i<=N;++i) read(V[i].w);
	read(id); capital=V+id;
	capital->pa=V;
	capital->BuildTree();
	for(Base=1;Base<=N;Base<<=1); newt=Base+1;
	capital->MakeChain();
	for(int l=Base>>1,r=newt>>1;r-l>1;l>>=1,r>>=1)
		for(i=l+1;i<r;++i) update(i);
	while(m--)
		switch(read(opt),opt){
			case 1: read(id); capital=V+id; break;
			case 2: read3(u,v,w); Modify(V+u,V+v,w); break;
			case 3: read(u); writeln(V[u].Query());
		}
	endPrint();
}

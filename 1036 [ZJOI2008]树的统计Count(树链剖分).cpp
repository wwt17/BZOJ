#include <cstdio>
inline int max(const int a,const int b){return a>b?a:b;}
inline void maxi(short &a,const short b){if(a<b)a=b;}
inline void read(short &a){
	char c;bool f;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	a=(f=c=='-')?0:c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
}
#define read2(a,b) (read(a),read(b))
inline void write(int a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))

//HLD
#define SizeN 30005
short N;
struct Seg{
	short Max; int Sum;
	Seg():Max(-32768){}
	inline void Modify(const short k){ Sum=k; Max=k; }
} Segmem[66000],*newSeg=Segmem;
inline void update(Seg* a,int i){
	a[i].Max=max(a[i<<1].Max,a[i<<1^1].Max);
	a[i].Sum=a[i<<1].Sum+a[i<<1^1].Sum;
}
inline short SegMax(Seg* a,unsigned short s,unsigned short t){
	short ans=-32768;
	for(s--,t++;s^t^1;s>>=1,t>>=1){
		if(~s&1) maxi(ans,a[s^1].Max);
		if( t&1) maxi(ans,a[t^1].Max);
	}
	return ans;
}
inline int SegSum(Seg* a,unsigned short s,unsigned short t){
	int ans=0;
	for(s--,t++;s^t^1;s>>=1,t>>=1){
		if(~s&1) ans+=a[s^1].Sum;
		if( t&1) ans+=a[t^1].Sum;
	}
	return ans;
}
struct Node;
struct Edge{
	Node* ed; Edge* next;
	//Edge(Node* _ed,Edge* _next):ed(_ed),next(_next){}
} E[SizeN<<1],*newE=E;
struct Node{
	Edge* son; Node *pa,*ch,*top; short w;unsigned short size,dep,loc; Seg *a;
	Node():son(NULL){}
	void addEdge(Node* ed){
		*newE=(Edge){ed,son}; son=newE++;
	}
	void BuildTree(Node* fa,int depth);
	void Modify(const int k);
} V[SizeN];
inline void addEdge(Node* a,Node* b){
	a->addEdge(b);
	b->addEdge(a);
}

void Node::BuildTree(Node* fa,int depth){
	pa=fa; dep=depth; size=1; int maxsize=0;
	for(Edge* e=son;e;e=e->next) if(fa!=e->ed){
		e->ed->BuildTree(this,depth+1);
		size+=e->ed->size;
		if(maxsize<e->ed->size) ch=e->ed,maxsize=e->ed->size;
	}
}
void MakeChain(){
	Node *u,*v; int cnt,Base;
	for(u=V+1;u<=V+N;++u) if(u->pa->ch!=u){
		for(cnt=1,v=u;v;++cnt,v=v->ch) v->top=u,v->a=newSeg;
		for(Base=1;Base<cnt;Base<<=1);Base--;
		for(cnt=1,v=u;v;++cnt,v=v->ch)
			newSeg[v->loc=Base+cnt].Modify(v->w);
		for(cnt=Base;cnt;--cnt) update(newSeg,cnt);
		newSeg+=(Base+1)<<1;
	}
}

void Node::Modify(const int k){
	a[loc].Modify(k);
	for(int x=loc>>1;x;x>>=1) update(a,x);
}
Node* LCA(Node* a,Node* b){
	while(a->top!=b->top)
		if(a->top->dep>b->top->dep)
		     a=a->top->pa;
		else b=b->top->pa;
	return a->dep<b->dep?a:b;
}
short lineMax(Node* x,Node* y){
	if(x->top==y->top) return SegMax(x->a,y->loc,x->loc);
	short ans=SegMax(x->a,x->top->loc,x->loc);
	for(x=x->top->pa;x->top!=y->top;x=x->top->pa)
		maxi(ans,SegMax(x->a,x->top->loc,x->loc));
	maxi(ans,SegMax(x->a,y->loc,x->loc));
	return ans;
}
int lineSum(Node* x,Node* y){
	if(x->top==y->top) return SegSum(x->a,y->loc,x->loc);
	int ans=SegSum(x->a,x->top->loc,x->loc);
	for(x=x->top->pa;x->top!=y->top;x=x->top->pa)
		ans+=SegSum(x->a,x->top->loc,x->loc);
	ans+=SegSum(x->a,y->loc,x->loc);
	return ans;
}
short Max(Node* a,Node* b){
	Node* lca=LCA(a,b);
	return max(lineMax(a,lca),lineMax(b,lca));
}
int Sum(Node* a,Node* b){
	Node* lca=LCA(a,b);
	return lineSum(a,lca)+lineSum(b,lca)-lca->a[lca->loc].Sum;
}

int main(){
	short i,a,b; int q; char opt;
	read(N);
	for(i=1;i<N;++i) read2(a,b),addEdge(V+a,V+b);
	for(i=1;i<=N;++i) read(V[i].w);
	V->top=V;
	V[1].BuildTree(V,1);
	MakeChain();
	scanf("%d\n",&q);
	while(q--)
		switch(opt=(getchar(),getchar()),read2(a,b),opt){
			case 'H':V[a].Modify(b);break;
			case 'M':writeln(Max(V+a,V+b));break;
			case 'S':writeln(Sum(V+a,V+b));
		}
}

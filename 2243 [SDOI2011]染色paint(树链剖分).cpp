#include <cstdio>
inline int max(const int a,const int b){return a>b?a:b;}
inline void maxi(int &a,const int b){if(a<b)a=b;}
inline void read(int &a){
    char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
    for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read(a),read(b),read(c))
inline void write(int a){
    if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))
 
//HLD
#define SizeN 100005
int N;
struct Seg{
    int lc,rc,sum; bool cov;
    inline void Cover(const int c){ lc=rc=c; sum=1; cov=true; }
    friend Seg operator + (const Seg &a,const Seg &b){
        return (Seg){a.lc,b.rc,a.sum+b.sum-(a.rc==b.lc),false};
    }
} Segmem[400005],*newSeg=Segmem;
inline void update(Seg* a,int i){
    a[i]=a[i<<1]+a[i<<1^1];
}
inline void down(Seg* a,int i){
    if(a[i].cov) {a[i<<1].Cover(a[i].lc);a[i<<1^1].Cover(a[i].rc);a[i].cov=false;}
}
void correct(Seg* a,int i){
    if(i>>=1) {correct(a,i);down(a,i);}
}
void SegCover(Seg* a,int s,int t,const int c){
    for(correct(a,--s),correct(a,++t);s^t^1;update(a,s>>=1),update(a,t>>=1)){
        if(~s&1) a[s^1].Cover(c);
        if( t&1) a[t^1].Cover(c);
    }
    while(s>>=1) update(a,s);
}
Seg SegSum(Seg* a,int s,int t){
    correct(a,s);correct(a,t);
    Seg suml=(Seg){a[s].lc,a[s].lc,1,false},
        sumr=(Seg){a[t].rc,a[t].rc,1,false};
    for(correct(a,--s),correct(a,++t);s^t^1;s>>=1,t>>=1){
        if(~s&1) suml=suml+a[s^1];
        if( t&1) sumr=a[t^1]+sumr;
    }
    suml=suml+sumr;
    return suml;
}
 
struct Node;
struct Edge{
    Node* ed; Edge* next;
} E[SizeN<<1],*newE=E;
struct Node{
    Edge* son; Node *pa,*ch,*top; int c,size,dep,loc; Seg *a;
    Node():son(NULL){}
    void addEdge(Node* ed){
        *newE=(Edge){ed,son}; son=newE++;
    }
    void BuildTree();
} V[SizeN];
inline void addEdge(Node* a,Node* b){
    a->addEdge(b);
    b->addEdge(a);
}
 
void Node::BuildTree(){
    size=1; int maxsize=0;
    for(Edge* e=son;e;e=e->next) if(e->ed!=pa){
        e->ed->pa=this;
        e->ed->dep=dep+1;
        e->ed->BuildTree();
        size+=e->ed->size;
        if(maxsize<e->ed->size) ch=e->ed,maxsize=e->ed->size;
    }
}
void MakeChain(){
    Node *u,*v; int cnt,Base;
    for(u=V+1;u<=V+N;++u) if(u->pa->ch!=u){
        for(cnt=1,v=u;v;++cnt,v=v->ch) v->top=u,v->a=newSeg;
        for(Base=1;Base<cnt;Base<<=1);
        for(cnt=1,v=u;v;++cnt,v=v->ch)
            newSeg[v->loc=Base+cnt].Cover(v->c);
        for(cnt=Base;cnt;--cnt) update(newSeg,cnt);
        newSeg+=Base<<1;
    }
}
 
Node* LCA(Node* a,Node* b){
    while(a->top!=b->top)
        if(a->top->dep>b->top->dep)
             a=a->top->pa;
        else b=b->top->pa;
    return a->dep<b->dep?a:b;
}
void linePaint(Node* x,Node* y,int c){
    if(x->top==y->top) return SegCover(x->a,y->loc,x->loc,c);
    SegCover(x->a,x->top->loc,x->loc,c);
    for(x=x->top->pa;x->top!=y->top;x=x->top->pa)
        SegCover(x->a,x->top->loc,x->loc,c);
    SegCover(x->a,y->loc,x->loc,c);
}
Seg lineSum(Node* x,Node* y){
    if(x->top==y->top) return SegSum(x->a,y->loc,x->loc);
    Seg ans=SegSum(x->a,x->top->loc,x->loc);
    for(x=x->top->pa;x->top!=y->top;x=x->top->pa)
        ans=SegSum(x->a,x->top->loc,x->loc)+ans;
    return SegSum(x->a,y->loc,x->loc)+ans;
}
void Paint(Node* a,Node* b,int c){
    Node* lca=LCA(a,b);
    linePaint(a,lca,c); linePaint(b,lca,c);
}
int Sum(Node* a,Node* b){
    Node* lca=LCA(a,b);
    return lineSum(a,lca).sum+lineSum(b,lca).sum-1;
}
 
int main(){
    int m,i,a,b,c;
    read2(N,m);
    for(i=1;i<=N;++i) read(V[i].c);
    for(i=1;i<N;++i) read2(a,b),addEdge(V+a,V+b);
    V->top=V;
    V[1].pa=V;V[1].dep=1;
    V[1].BuildTree();
    MakeChain();
    char opt;
    while(m--){
				while((opt=getchar())!='C'&&opt!='Q');
        switch(opt){
            case 'C': read3(a,b,c); Paint(V+a,V+b,c); break;
            default : read2(a,b); writeln(Sum(V+a,V+b));
        }
    }
    return 0;
}

#include <cstdio>
#include <cstdlib>
#define size 30001
#define sizeT 131072
int N,m,i,P,W,D,w,q,u,v,s,t,Ret;
int max(const int& a,const int& b) { a>b?a:b; }
struct Ttype {
	int max,sum;
	inline void change(const int& w) { max=sum=w; }
} T[sizeT];
struct node {
    int son,l,r;
    inline void change() {
			for (T[s=l].change(v);s^1;s=t) {
				t=s<<1;
				T[t].max=max(T[s].max,T[s^1].max);
				T[t].sum=T[s].sum+T[s^1].sum;
			}
			for (T[t=r].change(v);t^1;t=s) {
				s=t<<1;
				T[s].max=max(T[t].max,T[t^1].max);
				T[s].sum=T[t].sum+T[t^1].sum;
			}
		}
} n[size];
inline int max() {
	Ret=-30000;
	for (s=n[u].r-1,t=n[v].l+1;s^1^t;s<<=1,t<<=1) {
		if (!(s&1)) Ret=max(Ret,T[s^1].max);
		if (  t&1 ) Ret=max(Ret,T[t^1].max);
	}
	return Ret;
}
inline int sum() {
	Ret=0;
	for (s=n[u].r-1,t=n[v].l+1;s^1^t;s<<=1,t<<=1) {
		if (!(s&1)) Ret+=T[s^1].sum;
		if (  t&1 ) Ret+=T[t^1].sum;
	}
}
struct edge {
    int link,next;
    void init(int a,int b) {
        link=b;
        next=n[a].son;
        n[a].son=m;
    }
} e[size<<1];
void DFS(int u,int f) {
    n[u].l=++D;
    int v;
    for (int i=n[u].son;i;i=e[i].next)
        if ((v=e[i].link)!=f)
            DFS(v,u);
    n[u].r=++D;
}
int main() {
    scanf("%d",&N);
    for (i=N-1;i;--i) {
        scanf("%d%d",&u,&v);
        e[++m].init(u,v);
        e[++m].init(v,u);
    }
    D=N<<1;
    for (W=1;W<D;W<<=1);
    D=W;
    DFS(1,0);
    for (i=W+1;i<=W+N;++i) {
			scanf("%d",&w);
			T[i].change(w);
		}
		for (i=W;i;--i) {
			T[i].max=max(T[i<<1].max,T[(i<<1)+1].max);
			T[i].sum=T[i<<1].sum+T[(i<<1)+1].sum;
		}
		char opt[8];
		scanf("%d",&q);
    while (q--) {
				scanf("%s%d%d",opt,&u,&v);
				switch (opt[1]) {
					case 'H': n[u].change(); break;
					case 'M': printf("%d\n",max()); break;
					case 'S': printf("%d\n",sum()); break;
				}
    }
    system("pause");
}

/**************************************************************
    Problem: 1782
    User: wwt15
    Language: C++
    Result: Accepted
    Time:356 ms
    Memory:6040 kb
****************************************************************/
 
#include <cstdio>
#define size 100001
#define sizeT 524288
int N,m,i,A,B,P,T[sizeT],W,D;
struct node {
    int son,l,r;
    int arrive() {
        int s,t,Ret=0;
        for (s=l;s;s>>=1) Ret+=T[s];
        for (s=l-1,t=r+1;s^1^t;s>>=1,t>>=1) {
            if (!(s&1)) ++T[s^1];
            if (  t&1 ) ++T[t^1];
        }
        return Ret;
    }
} n[size];
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
    scanf("%d\n",&N);
    for (i=N-1;i;--i) {
        scanf("%d%d\n",&A,&B);
        e[++m].init(A,B);
        e[++m].init(B,A);
    }
    D=N<<1;
    for (W=1;W<D;W<<=1);
    D=W;
    DFS(1,0);
    for (i=N;i;--i) {
        scanf("%d\n",&P);
        printf("%d\n",n[P].arrive());
    }
}

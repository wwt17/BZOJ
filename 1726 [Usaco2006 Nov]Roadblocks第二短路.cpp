/**************************************************************
    Problem: 1726
    User: wwt15
    Language: C++
    Result: Accepted
    Time:108 ms
    Memory:3260 kb
****************************************************************/
 
#include <cstdio>
#include <queue>
using namespace std;
#define sizeN 5005
#define size2M 200005
#define oo 0x70000000
int K,S,T,N,M,m,X,Y,W,i,Ret;
struct node {
    int son,h,cnt;
    bool inq;
    void init() {
        //inq=false;
    }
} n[sizeN];
struct edge {
    int w,link,next;
    void init(int x,int y) {
        w=W;
        link=y;
        next=n[x].son;
        n[x].son=m;
    }
} e[size2M];
bool relaxed(int &a,int b) {
    if (a>b) { a=b; return true; }
    return false;
}
void Initialize() { //SPFA h to T
    for (X=1;X<=N;++X) n[X].h=oo;
    queue<int> q;
    for (n[T].inq=true,n[T].h=0,q.push(T);!q.empty();n[X].inq=false,q.pop())
        for (i=n[X=q.front()].son;i;i=e[i].next)
            if (relaxed(n[Y=e[i].link].h,n[X].h+e[i].w)&&!n[Y].inq)
                n[Y].inq=true,q.push(Y);
}
struct elem {
    int s,f,g;
    friend bool operator < (elem a,elem b)
        { return a.f>b.f; }
};
int Ans() { //Astar f[i]=g[i]+h[i] //BFS
    if (S==T) ++K;
    for (X=1;X<=N;++X) n[X].init();
    priority_queue<elem> q;
    elem x,y={S,n[S].h,0};
    q.push(y);
    while (!q.empty()) {
        x=q.top(),q.pop();
        X=x.s;
        if (++n[X].cnt>K) continue;
        if (X==T&&n[X].cnt==K) return x.g;
        for (i=n[X].son;i;i=e[i].next)
            y.s=Y=e[i].link, y.f=(y.g=x.g+e[i].w)+n[Y].h,
            q.push(y);
    }
    return -1;
}
int main() {
    scanf("%d%d\n",&N,&M);
    S=1,T=N,K=2;
    for (i=1;i<=M;++i) {
        scanf("%d%d%d\n",&X,&Y,&W);
        e[++m].init(X,Y);
        e[++m].init(Y,X);
    }
    Initialize();
    printf("%d\n",Ans());
}

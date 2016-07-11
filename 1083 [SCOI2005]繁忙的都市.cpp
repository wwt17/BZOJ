/**************************************************************
    Problem: 1083
    User: wwt15
    Language: C++
    Result: Accepted
    Time:32 ms
    Memory:1332 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
using namespace std;
#define sizeN 301
#define sizeM 90000
int n,m,i,sum;
struct Disjoint_set {
    short v[sizeN];
    void init() {
        for (int k=1;k<sizeN;++k)
            v[k]=k;
    }
    short belong(short k) {
        if (v[k]==k) return k;
        return v[k]=belong(v[k]);
    }
    void merger(int x,int y) {
        v[y]=x;
    }
} s;
struct road {
    short u,v,c;
    void input()
        { scanf("%d%d%d\n",&u,&v,&c); }
    friend bool operator < (const road& a,const road& b)
        { return a.c<b.c; }
    void link() {
        int x=s.belong(u),y=s.belong(v);
        if (x^y) {
            s.merger(x,y);
            if (++sum==n-1) {
                printf("%d %d\n",sum,c);
                exit(0);
            }
        }
    }
} r[sizeM];
int main() {
    scanf("%d%d\n",&n,&m);
    for (i=0;i<m;++i) r[i].input();
    sort(r,r+m);
    s.init();
    for (i=0;i<m;++i) r[i].link();
}

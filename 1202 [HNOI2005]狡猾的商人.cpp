/**************************************************************
    Problem: 1202
    User: wwt15
    Language: C++
    Result: Accepted
    Time:208 ms
    Memory:808 kb
****************************************************************/
 
#include <cstdio>
int w,n,m,f[100],g[100],s,t,v,x,y;
int belong(int k) {
    if (f[k]==k) return k;
    int tmp=f[k];
    f[k]=belong(f[k]);
    g[k]+=g[tmp];
    return f[k];
}
bool res;
int main() { for (scanf("%d",&w);w;--w) {
    scanf("%d%d",&n,&m);
    for (x=0;x<=n;++x) f[x]=x,g[x]=0;
    res=true;
    while (m--) {
        scanf("%d%d%d",&s,&t,&v);
        --s;
        if ((x=belong(s))==(y=belong(t)))
               g[t]-g[s]==v?0:res=false;
        else f[y]=x,g[y]=g[s]+v-g[t];
    }
    if (res) printf("true\n"); else printf("false\n");
}}

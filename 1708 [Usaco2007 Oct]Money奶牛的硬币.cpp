/**************************************************************
    Problem: 1708
    User: wwt15
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:812 kb
****************************************************************/
 
#include <cstdio>
#include <cstring>
int main() {
    int V,N,v,m,n,l;
    scanf("%d%d\n",&V,&N);
    long long f[10001];
    memset(f,0,sizeof(f));
    f[0]=1;
    for (v=0;v<V;++v)
        for (m=0,scanf("%d\n",&n);n<=N;++m,++n)
            f[n]+=f[m];
    printf("%lld\n",f[N]);
}

/**************************************************************
    Problem: 1704
    User: wwt15
    Language: C++
    Result: Accepted
    Time:220 ms
    Memory:816 kb
****************************************************************/
 
#include <cstdio>
#include <cstdlib>
#define size 5000
#define inf 0x7fffffff
int N,i,j,K,k,M,m;
bool a[size],b[size],f,succeeded;
char c;
int main() {
    scanf("%d\n",&N);
    succeeded=true;
    for (i=0;i<N;++i) {
        scanf("%c\n",&c);
        if (a[i]=c=='B') succeeded=false;
    }
    if (succeeded) { printf("0 0\n"); exit(0); }
    M=K=inf;
    for (k=1;k<=N;++k) {
        m=0;
        f=0;
        for (i=0,b[j=k-1]=0;j<N;++i,++j) {
            b[j]=f;
            if (a[i]^b[i]^f) f^=1,++m;
        }
        succeeded=true;
        for (;i<N;++i) if (a[i]^b[i]^f)
            { succeeded=false; break; }
        if (succeeded&&M>m) K=k,M=m;
    }
    printf("%d %d\n",K,M);
}

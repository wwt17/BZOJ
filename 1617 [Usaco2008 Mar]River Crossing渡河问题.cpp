/**************************************************************
    Problem: 1617
    User: wwt15
    Language: C++
    Result: Accepted
    Time:36 ms
    Memory:804 kb
****************************************************************/
 
#include <cstdio>
#define size 2501
inline void mini(int &a,int b)
    { if (a>b) a=b; }
int main() {
    int N,M,i,j,m[size],f[size];
    scanf("%d%d\n",&N,&M);
    m[0]=M<<1;
    f[0]=0;
    for (i=1;i<=N;++i) {
        scanf("%d",&m[i]);
        f[i]=m[i]+=m[i-1];
        for (j=1;j<i;++j) {
            mini(f[i],f[j]+m[i-j]);
        }
    }
    printf("%d\n",f[N]-M);
}

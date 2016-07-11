/**************************************************************
    Problem: 1012
    User: wwt15
    Language: C++
    Result: Accepted
    Time:496 ms
    Memory:2296 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
#define size 200005
int main() {
    int M,D,s[size],a[size],L,n,t=0;
    s[0]=a[0]=0;
    char opt;
    scanf("%d%d\n",&M,&D);
    while (M--) {
        scanf("%c",&opt);
        if (opt=='Q') {
            scanf("%d\n",&L);
            printf("%d\n",t=a[s[std::lower_bound(s+1,s+s[0],a[0]-L+1)-s]]);
        } else {
            scanf("%d\n",&n);
            for (a[++a[0]]=n=(n+t)%D;s[0]&&a[s[s[0]]]<=n;--s[0]);
            s[++s[0]]=a[0];
        }
    }
}

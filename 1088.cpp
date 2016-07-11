/**************************************************************
    Problem: 1088
    User: wwt15
    Language: C++
    Result: Accepted
    Time:12 ms
    Memory:812 kb
****************************************************************/
 
#include <cstdio>
#include <cstdlib>
#define size 10001
int ans=0;
inline void print() {
    printf("%d\n",ans);
    exit(0);
}
int main() {
    int N,i,f[size],a[size];
    scanf("%d\n%d",&N,&a[0]);
    switch (a[0]) {
        case 0:
            f[0]=0,f[1]=0;
            break;
        case 1:
            f[0]=0,f[1]=1;
            break;
        case 2:
            f[0]=1,f[1]=1;
            break;
        default:
            print();
    }
    for (i=1;i<N;++i) {
        scanf("%d",&a[i]);
        if ((f[i+1]=a[i]-(f[i-1]+f[i]))>>1) break;
    }
    ans=i==N&&!f[i]?1:0;
    if (a[0]^1) print();
    int j;
    f[0]=1,f[1]=0;
    for (j=1;j<N;++j)
        if ((f[j+1]=a[j]-(f[j-1]+f[j]))>>1) break;
    ans+=j==N&&!f[j]?1:0;
    print();
}

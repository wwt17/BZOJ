#include <cstdio>
#include <cmath>
#include <cstdlib>
#define n 10
#define l 10000
int main() {
    printf("%d %d\n",n,l);
    int i,t=0;
    bool ans[n];
    for (i=1;t!=n;++i) ans[t++]=!ans[i];
    for (i=0;i<n;++i)
        printf("%c",ans[i]?'a':'b');
    printf("\n");
    system("pause");
}

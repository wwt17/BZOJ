/**************************************************************
    Problem: 1724
    User: wwt15
    Language: C++
    Result: Accepted
    Time:20 ms
    Memory:884 kb
****************************************************************/
 
#include <cstdio>
int n,h[20001],i,len;
long long ans=0;
void swap(int a,int b)
 { int t=h[a]; h[a]=h[b]; h[b]=t; }
void down(int i){
    for (int j=i<<1;i<=(n>>1);i=j,j=i<<1){
        if (j+1<=n&&h[j]>h[j+1]) ++j;
      if (h[i]>h[j]) swap(i,j);
      else break;
  }
}
int main(){
    scanf("%d\n",&n);
    for (i=1;i<=n;++i) scanf("%d\n",&h[i]);
    for (i=n>>1;i;--i) down(i);
    for (;n>1;){
        len=h[1];
        h[1]=h[n--];
        down(1);
        h[1]+=len;
        ans+=h[1];
        down(1);
    }
    printf("%lld\n",ans);
}

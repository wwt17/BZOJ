#include <cstdio>
#include <algorithm>
#define size 1000001
inline void read(int &a){
    char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
    for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read(a),read(b),read(c)
inline void write(int a){
    if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) write(a),putchar('\n')
int N,M,m,i,x,sum,c[size],t[size],p[size],pp[size],Ans[size];
struct flower{ int l,r,*ans; } f[size];
inline bool cmp(const flower &a,const flower &b)
    { return a.r<b.r; }
int main(){
    read3(N,*c,M);
    for(i=1;i<=N;++i) read(c[i]);
    for(i=1;i<=M;++i) read2(f[i].l,f[i].r),f[i].ans=Ans+i;
    std::sort(f+1,f+M+1,cmp);
    m=1;
    for(i=1;i<=N;++i){
        int ch=c[i];
        for(x=pp[ch]+1;x<=N;x+=x&-x) ++t[x];
        for(x= p[ch]+1;x<=N;x+=x&-x) --t[x];
        pp[ch]=p[ch];
        p[ch]=i;
        while(m<=M&&f[m].r==i){
            sum=0;
            for(x=f[m].l;x;x-=x&-x) sum+=t[x];
            *f[m].ans+=sum;
            ++m;
        }
    }
    for(i=1;i<=M;++i) writeln(Ans[i]);
}

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
#define Sp system("pause")
inline void read(int &a){
	char c;for(c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for(c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+c-'0';
}
inline void write(int a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
int N,cnt; float tmp,ans;
struct car{
	int k,v; bool win;
} g[10001],*p[10001],*i,**ii,**jj,**kk;
inline bool cmp(car* a,car* b){
	return a->k<b->k||a->k==b->k&&a->v>b->v;
}
int main(){
	read(N);
	for(i=g+1;i<=g+N;++i) read(i->k);
	for(i=g+1,ii=p+1;i<=g+N;++i,++ii) read(i->v),*ii=i;
	std::sort(p+1,p+N+1,cmp); *p=g;
	for(ii=p+N;ans<1e15;(*ii)->win=true,++cnt,ii=kk){
		while(ii>p+1&&(*(ii-1))->k==(*ii)->k) (*ii)->win=true,++cnt,--ii;
		for(ans=1e16,jj=ii-1;jj>p;--jj){
			tmp=(*jj)->v-(*ii)->v;
			if(tmp<0) continue;
			if((tmp=((*ii)->k-(*jj)->k)/tmp)<ans)
				ans=tmp,kk=jj;
		}
	}
	write(cnt); putchar('\n'); if(!cnt) return 0; bool first=true;
	for(i=g+1;i<=g+N;++i) if(i->win)
		first?first=false:putchar(' '),write(i-g);
	putchar('\n');
}

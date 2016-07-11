#include <cstdio>
#include <algorithm>
using namespace std;
inline int gcd(int a,int b){
	static int t;
	while(b) t=a,a=b,b=t%b;
	return a;
}
const int size=222;
typedef pair<unsigned short,unsigned short> query;
#define l first
#define r second
int N,M,X,Y,x[50001],y[50001]; unsigned short C[50001],cnt[50001];
query q[50000],*o[50000],cur;
inline bool cmp(const query* a,const query* b){
	return a->l/size==b->l/size?a->l/size&1^(a->r<b->r):a->l<b->l;
}
int main(){
	scanf("%u%u",&N,&M);
	for(int i=1;i<=N;i++) scanf("%hu",C+i);
	for(int i=0;i<M;i++) scanf("%hu%hu",&q[i].l,&q[i].r),o[i]=q+i;
	sort(o,o+M,cmp); cnt[0]=1;
	for(int i=0;i<M;i++){
		query &t=*o[i];
		while(cur.l>t.l) X+=cnt[C[--cur.l]]++;
		while(cur.r<t.r) X+=cnt[C[++cur.r]]++;
		while(cur.l<t.l) X-=--cnt[C[cur.l++]];
		while(cur.r>t.r) X-=--cnt[C[cur.r--]];
		int Y=(long long)(t.r-t.l)*(1+t.r-t.l)>>1,g=gcd(X,Y);
		x[o[i]-q]=X/g; y[o[i]-q]=Y/g;
	}
	for(int i=0;i<M;i++) printf("%u/%u\n",x[i],y[i]);
}

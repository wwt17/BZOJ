#include <cstdio>
#include <algorithm>
using namespace std;
int N,M,Base,i,Ans;
#define tension(a,b) if(a>b) a=b
struct data{
	int Min,Dec;
	inline void dec(const int x){
		Dec+=x; Min-=x;
	}
} C[231074];
#define update(i) C[i].Min=min(C[i<<1].Min,C[i<<1|1].Min)
#define down(i) C[i<<1].dec(C[i].Dec),C[i<<1|1].dec(C[i].Dec),C[i].Dec=0
inline void correct(int i){
	if(i>>=1){ correct(i); down(i); }
}
struct interval{
	int A,B;
	inline bool attempt(){
		static int l,r,bound;
		for(correct(l=A+=Base-1),correct(r=B+=Base+1),bound=N;l^r^1;l>>=1,r>>=1){
			if(!(l&1)) tension(bound,C[l^1].Min);
			if(  r&1 ) tension(bound,C[r^1].Min);
		}
		if(!bound) return false;
		for(l=A,r=B;l^r^1;l>>=1,update(l),r>>=1,update(r)){
			if(!(l&1)) C[l^1].dec(1);
			if(  r&1 ) C[r^1].dec(1);
		}
		while(l>>=1) update(l);
		return true;
	}
} a[100000];
inline bool cmp(const interval a,const interval b){
	return a.B < b.B || a.B == b.B && a.A > b.A;
}
int main(){
	scanf("%u%u",&N,&M);
	for(Base=1;Base<=N;Base<<=1);
	for(i=1;i<=N;i++) scanf("%u",C+(Base+i));
	for(int l=Base>>1,r=(Base+N+1)>>1;l^r^1;l>>=1,r>>=1)
		for(i=l+1;i<r;i++) update(i);
	for(i=0;i<M;i++) scanf("%u%u",a+i,(int*)(a+i)+1);
	sort(a,a+M,cmp);
	for(i=0;i<M;i++) if(a[i].attempt()) Ans++;
	printf("%u\n",Ans);
}

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n,a[50001],*ord[50001],q,size;
typedef pair<unsigned short,unsigned short> query;
#define l first
#define r second
query Q[50000],*p[50000],cur(1,0); unsigned ans,t[50002],T,Ans[50000];
inline bool cmpip(const int *a,const int *b){
	return *a < *b;
}
inline bool cmp(const query *a,const query *b){
	return a->l/size==b->l/size
		? a->l/size&1^(a->r<b->r)
		: a->l<b->l;
}
inline void dec(int x){
	for(;x<=T;x+=x&-x) t[x]--;
}
inline void inc(int x){
	for(;x<=T;x+=x&-x) t[x]++;
}
inline unsigned minsum(int x){
	unsigned ret=0;
	for(x--;x;x-=x&-x) ret+=t[x];
	return ret;
}
inline unsigned maxsum(int x){
	return cur.r-cur.l+1-minsum(x+1);
}
int main(){
	scanf("%u",&n);
	size=(int)sqrt(n);
	for(int i=1;i<=n;i++) scanf("%u",ord[i]=a+i); ord[n+1]=a;
	sort(ord+1,ord+n+1,cmpip);
	T=1;
	for(int i=1;i<=n;i++) *ord[i]=*ord[i]==*ord[i+1]?T:T++;
	scanf("%u",&q);
	for(int i=0;i<q;i++) scanf("%u%u",&Q[i].l,&Q[i].r),p[i]=Q+i;
	sort(p,p+q,cmp);
	for(int i=0;i<q;i++){
		query now=*p[i];
		while(cur.l<now.l) dec(a[cur.l]),ans-=minsum(a[cur.l++]);
		while(cur.l>now.l) inc(a[--cur.l]),ans+=minsum(a[cur.l]);
		while(cur.r>now.r) dec(a[cur.r]),ans-=maxsum(a[cur.r--]);
		while(cur.r<now.r) inc(a[++cur.r]),ans+=maxsum(a[cur.r]);
		Ans[p[i]-Q]=ans;
	}
	for(int i=0;i<q;i++) printf("%u\n",Ans[i]);
}

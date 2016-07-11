#include <cstdio>
#define maxn 100005
typedef long long data;
int N;
data a[maxn],b[maxn],c[maxn];
inline int lowbit(const int x){return x&-x;}
void update(data* a,int x,const data w){
	for (;x<=N;x+=lowbit(x)) a[x]+=w;
}
data query(data* a,int x){
	data ret=0;
	for (;x;x-=lowbit(x)) ret+=a[x];
	return ret;
}
inline void add(const int l,const int r,const data w){
	update(b,l,w);
	update(c,l,w*l);
	update(b,r+1,-w);
	update(c,r+1,-(r+1)*w);
}
inline data query(int l,int r){
	return a[r]-a[l-1]+((r+1)*query(b,r)-query(c,r))-(l*query(b,l-1)-query(c,l-1));
}
int main(){
	int i,M;
	scanf("%d%d",&N,&M);
	a[0]=0;
	for (i=1;i<=N;++i) scanf("%lld",&a[i]),a[i]+=a[i-1];
	int l,r; data w;
	while (M--)
		switch (getchar()){
			case 'C':scanf("%d%d%lld",&l,&r,&w);
				add(l,r,w);
				break;
			case 'Q':scanf("%d%d",&l,&r);
				printf("%lld\n",query(l,r));
				break;
			default:M++;
		}
}

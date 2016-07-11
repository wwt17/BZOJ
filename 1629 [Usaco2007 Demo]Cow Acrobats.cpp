#include <cstdio>
#include <algorithm>
#define inf 2000000000
int N,i;
struct cow {
	int w,s,sum;
	void read() {
		scanf("%d%d",&w,&s);
		sum=w+s;
	}
} c[50000];
inline bool cmp(const cow &a,const cow &b) {
	return a.sum<b.sum;
}
int main() {
	scanf("%d",&N);
	for (i=0;i<N;++i) c[i].read();
	std::sort(c,c+N,cmp);
	int sum=0,ans=-inf;
	for (i=0;i<N;++i) {
		sum-=c[i].s;
		ans=std::max(ans,sum);
		sum+=c[i].sum;
	}
	printf("%d\n",ans);
	//system("pause");
}

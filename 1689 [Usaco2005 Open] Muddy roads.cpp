#include <cstdio>
#include <algorithm>
int N,L,i,ans,sum,len;
struct pool{
	int s,t;
	friend bool operator < (const pool &a,const pool &b){
		return a.s<b.s||a.s==b.s&&a.t<b.t;
	}
} a[10000];
int main(){
	scanf("%d%d",&N,&L);
	for(i=0;i<N;++i) scanf("%d%d",&a[i].s,&a[i].t);
	std::sort(a,a+N);
	for(i=0;i<N;++i) if(len<a[i].t){
		if(len<a[i].s) len=a[i].s;
		sum=(a[i].t-len-1)/L+1;
		len+=sum*L;
		ans+=sum;
	}
	printf("%d\n",ans);
}

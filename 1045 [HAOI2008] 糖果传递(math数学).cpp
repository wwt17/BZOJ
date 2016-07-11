#include <cstdio>
#include <cstdlib>
#include <algorithm>
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
int n,i,a[1000001];
long long x,Ans,b[1000001];
int main(){
	read(n);
	for(i=1;i<=n;i++) read(a[i]),x+=a[i];
	x/=n;
	for(i=1;i<=n;i++){
		b[i]=b[i-1]-x+a[i];
	}
	std::nth_element(b+1,b+(n>>1),b+n+1);
	for(i=1;i<=n;i++) Ans+=labs(b[i]-b[n>>1]);
	printf("%llu\n",Ans);
}

#include <cstdio>
int n,i,a[100001];
long long x,y;
int main(){
	scanf("%u",&n);
	for(i=1;i<=n;i++){
		scanf("%u",a+i);
		(a[i]>a[i-1]?x:y)+=a[i]-a[i-1];
	}
	x-=a[1];
	if(x+y>0) printf("%lld\n%d\n",x,x+y+1);
	else printf("%lld\n%d\n",-y,-y-x+1);
}

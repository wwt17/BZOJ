#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=100005,T=100005;
int n,m,t,x[N],y[N];
ll b[N];
ll work(int n,int a[]){
	int ave=t/n;
	b[0]=0;
	for(int i=1;i<n;i++) b[i]=b[i-1]+a[i]-ave;
	nth_element(b,b+n/2,b+n);
	ll d=b[n/2],ans=0;
	for(int i=0;i<n;i++) ans+=abs(b[i]-d);
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(int k=0;k<t;k++){
		int i,j; scanf("%d%d",&i,&j);
		x[i]++;
		y[j]++;
	}
	if(t%n==0)
		if(t%m==0)
			printf("both %lld\n",work(n,x)+work(m,y));
		else
			printf("row %lld\n",work(n,x));
	else
		if(t%m==0)
			printf("column %lld\n",work(m,y));
		else
			puts("impossible");
}

#include <cstdio>
#include <algorithm>
using std::max;
const int N=15;
int k,n,m,score[N],front[N];
double f[1<<N];
int main(){
	scanf("%d%d",&k,&n); m=1<<n;
	for(int j=0;j<n;j++){
		scanf("%d",&score[j]);
		int x; scanf("%d",&x);
		while(x){ front[j]|=1<<x-1; scanf("%d",&x); }
	}
	while(k--)
		for(int i=0;i<m;i++){
			double sum=0;
			for(int j=0;j<n;j++)
				sum+=(i&front[j])==front[j]?max(f[i],f[i|1<<j]+score[j]):f[i];
			f[i]=sum/n;
		}
	printf("%lf\n",f[0]);
}

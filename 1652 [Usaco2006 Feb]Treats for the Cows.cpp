//f[i,j]=max(f[i+1,j]+v[i]*(i+N+1-j),f[i,j-1]+v[j]*(i+N+1-j))
#include <cstdio>
#include <algorithm>
inline int max(const int a,const int b) { return a>b?a:b; }
int main() {
	int N;
	scanf("%d",&N);
	int i,j,kth,v[N],f[N];
	for (j=0;j<N;++j) {
		scanf("%d",&v[j]);
		f[j]=v[j]*(kth=N);
		for (i=j-1,--kth;i>=0;--i,--kth)
			f[i]=max(f[i+1]+v[i]*kth,f[i]+v[j]*kth);
	}
	printf("%d\n",f[0]);
	system("pause");
}

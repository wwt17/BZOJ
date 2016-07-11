#include <cstdio>
#include <algorithm>
using namespace std;
#define maxint 0x7fffffff
void maxi(int &a,int b) { if (a<b) a=b; }
int main() {
	int N;
	scanf("%d\n",&N);
	int i,j,a[N],f[N],ans=0;
	for (i=0;i<N;++i) {
		scanf("%d",&a[i]);
		f[i]=0;
		for (j=0;j<i;++j) if (a[j]<a[i])
			maxi(f[i],f[j]);
		maxi(ans,++f[i]);
	}
	printf("%d\n",ans);
	system("pause");
}

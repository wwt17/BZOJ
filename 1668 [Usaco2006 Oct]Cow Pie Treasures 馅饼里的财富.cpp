#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
	int R,C,i,j;
	scanf("%d%d\n",&R,&C);
	int a[R][C];
	for (i=0;i<R;++i)
		for (j=0;j<C;++j)
			scanf("%d",&a[i][j]);
	int f[2][R],F=1;
	f[F][0]=a[0][0];
	for (i=1;i<R;++i) f[F][i]=0x80000000;
	for (j=1;j<C;++j) {
		F^=1;
		f[F][0]=max(f[F^1][0],f[F^1][1])+a[0][j];
		for (i=1;i<R-1;++i)
			f[F][i]=max(max(f[F^1][i-1],f[F^1][i]),f[F^1][i+1])+a[i][j];
		f[F][i]=max(f[F^1][i-1],f[F^1][i])+a[i][j];
	}
	printf("%d\n",f[F][R-1]);
	system("pause");
}

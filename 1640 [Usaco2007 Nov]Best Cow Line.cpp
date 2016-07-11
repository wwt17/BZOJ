#include <cstdio>
#include <algorithm>
int main() {
	int N,i,j,ii,jj,cnt=0;
	scanf("%d",&N);
	char c[N];
	for (j=0;j<N;++j) scanf("\n%c",&c[j]);
	for (i=0,--j;i<=j;cnt==80?(printf("\n"),cnt=1):++cnt,printf("%c",c[ii]<c[jj]?c[i++]:c[j--]))
		for (ii=i,jj=j;ii<=j&&jj>=i&&c[ii]==c[jj];++ii,--jj);
	printf("\n");
	system("pause");
}

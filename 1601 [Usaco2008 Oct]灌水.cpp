#include <stdio.h>
#include <stdlib.h>
#define size 1500
int n,i,j,k,v[size],p[size][size],sum;
bool f[size];
int main() {
	scanf("%d",&n);
	for (i=0;i<n;++i) scanf("%d\n",&v[i]);
	for (i=0;i<n;++i)
		for (j=0;j<n;++j)
			scanf("%d",&p[i][j]);
	for(k=0;k<n;++k) {
		sum=0x7fffffff;
		for (j=0;j<n;++j)
			if (!f[j]&&v[j]<sum)
				{ i=j; sum=v[j]; }
		f[i]=true;
		for (j=0;j<n;++j)
			if (!f[j]&&v[j]>p[i][j])
				v[j]=p[i][j];
	}
	sum=0;
	for (i=0;i<n;++i) sum+=v[i];
	printf("%d\n",sum);
}

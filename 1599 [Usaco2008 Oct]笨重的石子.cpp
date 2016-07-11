#include <cstdio>
#include <cstdlib>
int S1,S2,S3,a1,a2,a3,f[81];
int main() {
	scanf("%d%d%d",&S1,&S2,&S3);
	for (a1=S1;a1;--a1)
		for (a2=S2;a2;--a2)
			for (a3=S3;a3;--a3)
				++f[a1+a2+a3];
	int ans=0;
	for (int i=0;i<81;++i)
		if (f[ans]<f[i]) ans=i;
	printf("%d\n",ans);
}

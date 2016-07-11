#include <cstdio>
int N,M,W,D,j,f[12881];
void maxi(int &a,const int &b) {
	if (a<b) a=b;
}
int main() {
	scanf("%d%d",&N,&M);
	while (N--) {
		scanf("%d%d",&W,&D);
		for (j=M;j>=W;--j)
			maxi(f[j],f[j-W]+D);
	}
	printf("%d\n",f[M]);
}

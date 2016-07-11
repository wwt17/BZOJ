#include <cstdio>
#include <cstring>
#define P 1000007
int T,N,k,r,h[P];
bool f[P],first;
int main() { for(;;){
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&N);
		memset(f,0,sizeof(f));
		first=true;
		while (N--) {
			scanf("%d",&k);
			(r=k%P)<0?r=-r:0;
			while (f[r]&&h[r]^k) if (++r==P) r=0;
			if (f[r]) continue;
			f[r]=true,h[r]=k;
			first?first=false:printf(" ");
			printf("%d",k);
		}
		printf("\n");
	}
}}

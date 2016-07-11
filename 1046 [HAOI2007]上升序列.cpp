#include <cstdio>
#include <algorithm>
#include <functional>
#define SIZE 10002
int a[SIZE],s[SIZE],l[SIZE],*j,*k;
int N,M,i,len,ak;
int main(){
	scanf("%u",&N);
	j=s+1;
	for(i=1;i<=N;++i) scanf("%u",a+i);
	for(i=N;i;--i){
		k=std::lower_bound(s+1,j,a[i],std::greater<int>());
		*k=a[i];
		l[i]=k-s;
		if(j==k) ++j;
	}
	scanf("%u",&M);
	while(M--){
		scanf("%u",&len);
		if(!s[len]){
			puts("Impossible");
			continue;
		}
		ak=0;
		for(i=1;i<=N&&len;++i) if(l[i]>=len&&a[i]>ak)
			--len,ak?putchar(' '):0,printf("%u",ak=a[i]);
		putchar('\n');
	}
}

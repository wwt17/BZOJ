#include <stdio.h>
inline unsigned getint(){
	char c; while(c=getchar(),c<'0'||'9'<c); unsigned a=c-'0';
	while(c=getchar(),'0'<=c&&c<='9') a=a*10+c-'0'; return a;
}
int n,i,j,a[50001],Ans,flag;
#define work {\
	if(a[j]>a[i]) if(flag) break; else flag=1;\
	if(Ans<(a[j]^a[i])) Ans=a[j]^a[i];\
}
int main(){
	n=getint();
	for(i=1;i<=n;++i) a[i]=getint();
	for(i=1;i<=n;++i){
		for(j=i-1,flag=0;j>=1;--j) work;
		for(j=i+1,flag=0;j<=n;++j) work;
	}
	printf("%u\n",Ans);
	return 0;
}

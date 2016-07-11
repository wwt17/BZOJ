#include <cstdio>
short n,ans[5000],*high,*low,x;
#define mul(k) {\
	x=0;\
	for(short *i=low;i<high;i++){\
		x+=*i*k;\
		*i=x%10;\
		x/=10;\
	}\
	if(x) *high++=x;\
}
int main(){
	scanf("%u",&n);
	if(n==1) printf("1\n1\n");
	*ans=1; low=ans; high=low+1;
	for(;n>4 || n==3;n-=3) mul(3);
	for(;n;n-=2) mul(2);
	printf("%u\n",high-ans);
	if(high-low>100) low=high-100;
	for(short *i=high;i>low;putchar(*--i+'0'));putchar('\n');
}

#include <cstdio>
const int Base=100000000,
	table[]={0,1,2,3,4,5,6,9,12,16,20,27,36,48,64,81,108};
int n,i,ans[20000],len;
int main(){
	scanf("%u",&n);
	if(n<17){
		printf("%u\n",table[n]);
		return 0;
	}
	int sum2=4-n%5;
	n-=4;
	ans[len=1]=4;
	for(int i=0;i<sum2;i++) ans[1]*=3,n-=4;
	n/=5;
	for(int cnt=0;cnt<n;cnt++){
		int x=0;
		for(int i=1;i<=len;i++){
			x+=ans[i]*4;
			ans[i]=x%Base;
			x/=Base;
		}
		if(x) ans[++len]=x;
	}
	printf("%u",ans[len]);
	for(int i=len-1;i>0;i--) printf("%08u",ans[i]);
	putchar('\n');
}

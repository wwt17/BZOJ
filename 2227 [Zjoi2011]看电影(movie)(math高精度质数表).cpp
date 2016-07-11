// Ans=(k+1-n)*(k+1)^(n-1)/k^n
#include <cstdio>
const int base=10000,primes=46,prime[primes]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199};
int n,k,ans[primes];
void mul(int a,int q){
	for(int i=0;a!=1;i++)
		while(a%prime[i]==0) a/=prime[i],ans[i]+=q;
}
void mul(int *a,int b){
	int x=0;
	for(int i=1;i<=a[0];i++){
		x+=a[i]*b;
		a[i]=x%base;
		x/=base;
	}
	if(x) a[++a[0]]=x;
}
void print(int *a){
	printf("%d",a[a[0]]);
	for(int i=a[0]-1;i>0;i--)
		printf("%04d",a[i]);
}
void print(){
	static int x[125],y[125];
	x[0]=x[1]=y[0]=y[1]=1;
	for(int i=0;i<primes;i++){
		for(;ans[i]>0;ans[i]--) mul(x,prime[i]);
		for(;ans[i]<0;ans[i]++) mul(y,prime[i]);
	}
	print(x);
	putchar(' ');
	print(y);
	putchar('\n');
}
int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		if(n>k){ puts("0 1"); continue; }
		mul(k+1-n,1);
		mul(k+1,n-1);
		mul(k,-n);
		print();
	}
}

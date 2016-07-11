#include <cstdio>
int t,n,m,f[50];
int main(){
	for(f[0]=0,f[1]=1,m=2;(f[m]=f[m-1]+f[m-2])<=1e9;m++);
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0,j=m-1;i<=j;i++){
			for(;i<=j&&(long long)f[i]*f[j]>n;j--);
			if((long long)f[i]*f[j]==n){
				puts("TAK");
				goto next;
			}
		}
		puts("NIE");
		next:;
	}
}

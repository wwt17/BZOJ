#include <cstdio>
const int mo=10000;
int k,tot=1,f[2],g[2];
int power(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
int main(){
	scanf("%d",&k);
	f[0]=1;
	while(k--){
		int p,e; scanf("%d%d",&p,&e);
		tot=tot*power(p,e)%mo;
		if(p!=2){
			g[0]=(f[0]+f[1]*(p-1))%mo;
			g[1]=(f[1]+f[0]*(p-1))%mo;
			f[0]=g[0];
			f[1]=g[1];
		}
	}
	printf("%d\n%d\n%d\n",(f[0]+mo-1)%mo,f[1],(tot+mo*2-f[0]-f[1])%mo);
}

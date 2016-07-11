#include <cstdio>
const int N=1000005;
int n,q,k,*head,*tail,d[N],f[N],s[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",d+i);
	scanf("%d",&q);
	while(q--){
		scanf("%d",&k);
		head=tail=s;
		for(int i=1;i<=n;i++){
			for(;head<tail&&*head+k<i;head++);
			if(i>1) f[i]=f[*head]+(d[*head]<=d[i]);
			for(;head<tail&&(f[tail[-1]]==f[i]?d[tail[-1]]<d[i]:f[tail[-1]]>f[i]);tail--);
			*tail++=i;
		}
		printf("%d\n",f[n]);
	}
}

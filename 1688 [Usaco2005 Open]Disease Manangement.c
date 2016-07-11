#include <stdio.h>
unsigned short N,D,K,i,j,s,k,n,ans=0,d[1000],s1[32768],b;
int main(){
	scanf("%hu%hu%hu",&N,&D,&K);
	b=1<<D;
	for (i=0;i<N;++i)
		for (scanf("%hu",&s);s;--s)
			scanf("%hu",&k),d[i]|=1<<(k-1);
	for (j=0;j<b;++j) if ((s1[j]=s1[j>>1]+(j&1))==K){
		n=0;
		for (i=0;i<N;++i) if (!(d[i]&~j)) ++n;
		if (n>ans) ans=n;
	}
	printf("%hu\n",ans);
	return 0;
}

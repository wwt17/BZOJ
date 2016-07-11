#include <stdio.h>
short N,K,i,Ci,c[1001]; int Ans=0;
int main(){
	scanf("%d%d",&N,&K);
	for(i=1;i<=K;++i) scanf("%d",&Ci),++c[Ci];
	for(Ci=1000,--N;Ci&&N>0;!c[Ci]?--Ci:(--c[Ci],Ans+=Ci*N,N-=2));
	printf("%d\n",Ans);
	return 0;
}

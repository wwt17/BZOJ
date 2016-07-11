#include <stdio.h>
#include <string.h>
#define K 16
#define ll long long
int p,k;
ll m,n;
typedef ll line[K];
line memOpt[2][K],*Opt=memOpt[0],*opt=memOpt[1],*tmpOpt,memAns[2],C[K];
ll *Ans=memAns[0],*ans=memAns[1],*tmpAns;
inline void mulOpt(){
	int i,j,_k;
	for(i=0;i<=k;i++)
		for(j=0;j<=k;j++){
			opt[i][j]=0;
			for(_k=0;_k<=k;_k++)
				opt[i][j]=(opt[i][j]+Opt[i][_k]*Opt[_k][j]%p)%p;
		}
	tmpOpt=Opt,Opt=opt,opt=tmpOpt;
}
inline void mulAns(){
	int i,j;
	for(i=0;i<=k;++i){
		ans[i]=0;
		for(j=0;j<=k;++j)
			ans[i]=(ans[i]+Ans[j]*Opt[i][j]%p)%p;
	}
	tmpAns=Ans,Ans=ans,ans=tmpAns;
}
inline ll calc(ll n){
	memcpy(Opt,C,sizeof(C));
	for(;n;n>>=1,mulOpt())
		if(n&1)
			mulAns();
	return Ans[0];
}
inline ll prefixsum(int i){
	ll ret=0;
	for(;i;i--) ret+=Ans[i];
	return ret;
}
int main(){
	int i;
	scanf("%u",&k);
	for(i=1;i<=k;i++) scanf("%d",&Ans[k-i+1]),Ans[0]+=Ans[k-i+1];
	C[0][0]=1;
	for(i=1;i<=k;i++) scanf("%d",&C[1][i]),C[0][i]=C[1][i];
	for(i=2;i<=k;i++) C[i][i-1]=1;
	scanf("%llu%llu%u",&m,&n,&p); m--;
	ll tmp;
	printf("%u\n",(( m>k?(tmp=-calc(m-k),tmp+calc(n-m)):-prefixsum(m)+(n>k?calc(n-k):prefixsum(n)) )+p)%p);
}

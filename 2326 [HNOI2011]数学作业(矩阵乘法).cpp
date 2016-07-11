#include <cstdio>
long long n,M;
long long memAns[2][3],*Ans=memAns[0],*ans=memAns[1],*tmpAns;
typedef long long line[3];
line memOpt[2][3],*Opt=memOpt[0],*opt=memOpt[1],*tmpOpt;
void mulOpt(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			opt[i][j]=0;
			for(int k=0;k<3;k++)
				opt[i][j]=(opt[i][j]+Opt[i][k]*Opt[k][j])%M;
		}
	tmpOpt=Opt,Opt=opt,opt=tmpOpt;
}
void mulAns(){
	for(int i=0;i<3;i++){
		ans[i]=0;
		for(int j=0;j<3;j++)
			ans[i]=(ans[i]+Ans[j]*Opt[i][j])%M;
	}
	tmpAns=Ans,Ans=ans,ans=tmpAns;
}
int main(){
	scanf("%llu%u",&n,&M);
	long long base;
	for(base=1;n/(base*10);base*=10){
		Ans[0]=1;
		Opt[1][1]=base*10%M; Opt[1][2]=1; Opt[1][0]=1;
		Opt[2][1]=0; Opt[2][2]=1; Opt[2][0]=1;
		Opt[0][1]=0; Opt[0][2]=0; Opt[0][0]=1;
		for(long long k=9*base;k;k>>=1,mulOpt())
			if(k&1) mulAns();
	}
	Ans[0]=1;
	Opt[1][1]=base*10%M; Opt[1][2]=1; Opt[1][0]=1;
	Opt[2][1]=0; Opt[2][2]=1; Opt[2][0]=1;
	Opt[0][1]=0; Opt[0][2]=0; Opt[0][0]=1;
	for(long long k=n-base+1;k;k>>=1,mulOpt())
		if(k&1) mulAns();
	printf("%u\n",Ans[1]);
}

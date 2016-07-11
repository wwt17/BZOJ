#include <cstdio>
const int N=10,P=2009;
int n,b,t;
int memAns[2][90],*Ans=memAns[0],*ans=memAns[1],*tmpAns;
typedef int line[90];
line memOpt[2][90],*Opt=memOpt[0],*opt=memOpt[1],*tmpOpt;
#define f(i,j) ((i)*9+(j))
void mulOpt(){
	for(int i=0;i<b;i++)
		for(int j=0;j<b;j++){
			opt[i][j]=0;
			for(int k=0;k<b;k++)
				opt[i][j]+=Opt[i][k]*Opt[k][j];
			opt[i][j]%=P;
		}
	tmpOpt=Opt,Opt=opt,opt=tmpOpt;
}
void mulAns(){
	for(int i=0;i<b;i++){
		ans[i]=0;
		for(int j=0;j<b;j++)
			ans[i]+=Ans[j]*Opt[i][j];
		ans[i]%=P;
	}
	tmpAns=Ans,Ans=ans,ans=tmpAns;
}
int main(){
	scanf("%d%d\n",&n,&t); b=n*9;
	char c;
	for(int i=0;i<n;scanf("\n"),i++)
		for(int j=0;j<n;j++)
			if((c=getchar())>'0')
				Opt[f(j,c-'0'-1)][f(i,0)]++;
	for(int i=0;i<n;i++)
		for(int j=0;j<8;j++)
			Opt[f(i,j)][f(i,j+1)]++;
	Ans[f(0,0)]=1;
	for(;t;t>>=1,mulOpt())
		if(t&1) mulAns();
	printf("%d\n",Ans[f(n-1,0)]);
}

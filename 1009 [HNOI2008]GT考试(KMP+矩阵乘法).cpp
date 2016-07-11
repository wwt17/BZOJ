#include <cstdio>
#define SIZEM 24
int N,M,K,i,j; char s[SIZEM]; int p[SIZEM];
typedef int line[SIZEM];
line memOpt[2][SIZEM],*Opt=memOpt[0],*opt=memOpt[1],*tmpOpt;
int  memAns[2][SIZEM],*Ans=memAns[0],*ans=memAns[1],*tmpAns;
inline void mulOpt(){
	int i,j,k;
	for(i=0;i<M;i++)
		for(j=0;j<M;j++){
			opt[i][j]=0;
			for(k=0;k<M;k++)
				opt[i][j]=(opt[i][j]+Opt[i][k]*Opt[k][j])%K;
		}
	tmpOpt=Opt; Opt=opt; opt=tmpOpt;
}
inline void mulAns(){
	int i,j;
	for(i=0;i<M;i++){
		ans[i]=0;
		for(j=0;j<M;j++)
			ans[i]=(ans[i]+Ans[j]*Opt[i][j])%K;
	}
	tmpAns=Ans; Ans=ans; ans=tmpAns;
}
int main(){
	scanf("%u%u%u%s",&N,&M,&K,s+1);
	for(p[1]=0,j=0,i=2;i<=M;i++){
		while(j&&s[j+1]!=s[i]) j=p[j];
		if(s[j+1]==s[i]) j++;
		p[i]=j;
	}
	for(char c='0';c<='9';c++)
		for(i=0;i<M;i++){
			for(j=i;j&&s[j+1]!=c;j=p[j]);
			if(s[j+1]==c) j++;
			Opt[j][i]++;
		}
	Ans[0]=1;
	for(;N;N>>=1,mulOpt())
		if(N&1) mulAns();
	int a=0;
	for(j=0;j<M;j++) a=(a+Ans[j])%K;
	printf("%u\n",a);
}

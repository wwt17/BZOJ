#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Sp system("pause")
int f[1<<10][1000],d,i,j,k,bnd,Tmp,tmp,Factorial[11];
char s[12];
int main(){
	Factorial[0]=1;
	for (i=1;i<=10;++i)
		Factorial[i]=Factorial[i-1]*i;
int T;for (scanf("%d",&T);T;--T){
	scanf("%s%d",s,&d);
	bnd=1<<strlen(s);
	memset(f,0,sizeof(f));f[0][0]=1;
	for (k=0;k<bnd;++k)
		for (i=0;i<d;++i) if (f[k][i])
			for (j=0;s[j];++j)
				if (!(k&1<<j))
					f[k|1<<j][(i*10+(s[j]-'0'))%d]+=f[k][i];
	for (Tmp=1,i=0;i<=9;Tmp*=Factorial[tmp],++i)
		for (tmp=0,j=0;s[j];++j)
			if (i==s[j]-'0') ++tmp;
	printf("%d\n",f[bnd-1][0]/Tmp);
}}

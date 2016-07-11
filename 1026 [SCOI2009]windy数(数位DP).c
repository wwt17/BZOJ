//f[b][k]=sum{f[b-1]}-f[b-1][k-1]-f[b-1][k]-f[b-1][k+1]
//f[1][k]=1
#include <stdio.h>
char A[11],B[11];
unsigned memf[2][11],*F=memf[0],*f=memf[1],*tmp,sumA,sumB;
int b,i;
inline _Bool ok(int a,int b){
	return !a || b<(a&15)-1 || b>(a&15)+1;
}
inline void strrev(char *s){
	char *t,tmp;
	for(t=s;*t;t++); t--;
	for(;s<t;tmp=*s,*s=*t,*t=tmp,s++,t--);
}
int main(){
	scanf("%s%s",A,B);
	strrev(A); strrev(B);
	for(b=0;A[b]=='0';A[b++]='9'); --A[b];
	if(!A[b+1]&&A[b]=='0') A[b]='\0';
	for(b=0;B[b]=='9';B[b++]='0'); ++B[b];
	F[10]=1;
	for(b=0;A[b]||B[b];tmp=F,F=f,f=tmp,b++){
		for(f[10]=0,i=0;i<=9;i++)
			f[10]+=f[i]=F[10]-(i?F[i-1]:0)-F[i]-(i<9?F[i+1]:0);
		if(b&&!ok(A[b+1],A[b]&15)) sumA=0;
		for(i=(A[b]&15)+1;i<=9;i++)
			if(ok(A[b+1],i))
				sumA+=f[i];
		if(b&&!ok(B[b+1],B[b]&15)) sumB=0;
		for(i=(B[b]&15)-1;i>=0;i--)
			if(ok(B[b+1],i))
				sumB+=f[i];
	}
	printf("%u\n",sumA+sumB-F[10]);
}

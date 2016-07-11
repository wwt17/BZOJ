#include <cstdio>
typedef unsigned long long ull;
ull m,n,g,f[2][2][2],X; bool F;
ull mul(ull a,ull b){
	ull c=0;
	for(;b;b>>=1,a=(a<<1)%m) if(b&1) c=(c+a)%m;
	return c;
}
int main(){
	scanf("%I64u%I64u%I64u%I64u%I64u%I64u",&m,&f[F][0][0],&f[F][0][1],&X,&n,&g);
	f[F][1][0]=0;f[F][1][1]=1;
	for(;n;n>>=1){
		if(n&1) X=(mul(f[F][0][0],X)+f[F][0][1])%m;
		f[!F][0][0]=(mul(f[F][0][0],f[F][0][0])+mul(f[F][0][1],f[F][1][0]))%m;
		f[!F][0][1]=(mul(f[F][0][0],f[F][0][1])+mul(f[F][0][1],f[F][1][1]))%m;
		f[!F][1][0]=(mul(f[F][1][0],f[F][0][0])+mul(f[F][1][1],f[F][1][0]))%m;
		f[!F][1][1]=(mul(f[F][1][0],f[F][0][1])+mul(f[F][1][1],f[F][1][1]))%m;
		F^=1;
	}
	printf("%I64u\n",X%g);
}

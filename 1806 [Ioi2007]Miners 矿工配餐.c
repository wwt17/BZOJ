#include <string.h>
inline void maxi(int *a,const int b){if(*a<b)*a=b;}
typedef int situ[16];
int N;
situ mem[2][16],*F=mem[0],*f=mem[1],*tmp;
char ll,l,r,kind,val[64],have[4];
int main(){
	scanf("%u\n",&N);
	for(ll=0;ll<4;have[ll++]--) for(++have[ll],l=0;l<4;have[l++]--)
		for(++have[l],kind=0;kind<4;have[kind++]--){ ++have[kind];
			val[ll<<4|l<<2|kind]=(_Bool)have[1]+(_Bool)have[2]+(_Bool)have[3];
		}
	memset(mem,0x80,sizeof(mem));
	F[0][0]=0;
	while(N--){
		kind=getchar();
		switch(kind){
			case 'M': kind=1; break;
			case 'F': kind=2; break;
			case 'B': kind=3; break;
		}
		for(l=0;l<16;++l) for(r=0;r<16;++r){
			maxi(&f[l<<2&15|kind][r],F[l][r]+val[l<<2|kind]);
			maxi(&f[l][r<<2&15|kind],F[l][r]+val[r<<2|kind]);
			F[l][r]=0x80808080;
		}
		tmp=F,F=f,f=tmp;
	}
	int Ans=0;
	for(l=0;l<16;++l) for(r=0;r<16;++r) maxi(&Ans,F[l][r]);
	printf("%u\n",Ans);
	scanf("%u");
}

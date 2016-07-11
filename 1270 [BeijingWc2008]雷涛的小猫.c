#include <stdio.h>
#define size 2001
inline void read(unsigned* a){
	char c; for(c=getchar();c<'0'||'9'<c;c=getchar()); *a=c-'0';
	for(c=getchar();'0'<=c&&c<='9';c=getchar())*a=(*a)*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read(a),read(b),read(c))
inline unsigned max(unsigned a,unsigned b){return a>b?a:b;}
unsigned N,H,Delta,i,h,Ni,Tij,tmp,Tmp,f[size],m[size];
short sum[size][size];
int main(){
	read3(&N,&H,&Delta);
	for(i=1;i<=N;++i){
		read(&Ni);while(Ni--)
			read(&Tij),++sum[i][Tij];
	}
	for(h=H;h;--h){
		Tmp=0;
		if(h+Delta>H)
			for(i=1;i<=N;++i) Tmp=max(Tmp,f[i]+=sum[i][h]);
		else{
			tmp=m[h+Delta];
			for(i=1;i<=N;++i) Tmp=max(Tmp,f[i]=max(f[i],tmp)+sum[i][h]);
		}
		m[h]=Tmp;
	}
	printf("%d\n",Tmp);
}

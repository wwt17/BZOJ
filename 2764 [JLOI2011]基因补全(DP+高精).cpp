//f[i][j]=(pair(S[i],T[j])?f[i-1][j-1]:0)+f[i-1][j]
#include <cstdio>
#define SIZE 2005
struct huge{
	#define BASE 10000
	short a[100];
	huge& operator += (const huge &b){
		int i,k=0;
		if(*a<*b.a) *a=*b.a;
		for(i=1;i<=*a;i++){
			k+=a[i]+b.a[i];
			a[i]=k%BASE;
			k/=BASE;
		}
		if(k) a[++*a]=k;
		return *this;
	}
	void print(){
		int i;
		printf("%u",a[*a]);
		for(i=*a-1;i;i--)
			printf("%04u",a[i]);
	}
	#undef BASE
};
int n,m,i,j; huge f[SIZE];
char S[SIZE],T[SIZE];
inline bool pair(const char a,const char b){
	return a=='A'&&b=='T' || a=='C'&&b=='G'
	    || a=='T'&&b=='A' || a=='G'&&b=='C' ;
}
int main(){
	freopen("in.txt","r",stdin);
	scanf("%u%u%s%s",&n,&m,S+1,T+1);
	f[0].a[0]=f[0].a[1]=1;
	for(i=1;i<=n;++i)
		for(j=m;j;--j)
			if(pair(S[i],T[j]))
				f[j]+=f[j-1];
	f[m].print();
	putchar('\n');
	for(;;);
}

//f[n]=f[n-1]*3-f[n-2]+2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define situ_size 3
#define Base 10000
#define Huge_Num_size 1000
int N,i;
inline int max(const int a,const int b) { return a>b?a:b; }
struct Huge_Num {
	int size;
	short a[Huge_Num_size];
	Huge_Num() {
		memset(a,0,Huge_Num_size*sizeof(a[0]));
	}
	void init() { Huge_Num(); }
	void init(const short x) {
		size=1;
		a[0]=x;
	}
	void print() {
		if (!size) { printf("0"); return; }
		int i;
		for (printf("%d",a[size-1]),i=size-2;i>=0;--i) {
			if (a[i]<1000) printf("0");
			if (a[i]<100) printf("0");
			if (a[i]<10) printf("0");
			printf("%d",a[i]);
		}
		printf("\n");
	}
};
Huge_Num operator + (Huge_Num a,const short b) {
	int i=0,carry=b;
	while (carry) {
		carry+=a.a[i];
		a.a[i++]=carry%Base;
		carry/=Base;
	}
	if (i>a.size) a.size=i;
	return a;
}
Huge_Num operator - (Huge_Num a,Huge_Num b) {
	int i=0,carry=0;
	for (i=0;i<=a.size;++i) {
		carry+=a.a[i]-b.a[i];
		if (carry<0) a.a[i]=carry+Base,carry=-1;
		else a.a[i]=carry,carry=0;
	}
	return a;
}
Huge_Num operator * (Huge_Num a,const short b) {
	int i,carry=0;
	for (i=0;i<a.size;++i) {
		carry+=a.a[i]*b;
		a.a[i]=carry%Base;
		carry/=Base;
	}
	if (carry) a.a[a.size++]=carry;
	return a;
}
Huge_Num f[101];
int main() {
	scanf("%d",&N);
	f[0].init(0);
	f[1].init(1);
	for (i=2;i<=N;++i)
		f[i]=f[i-1]*3-f[i-2]+2,f[i].print();
	f[N].print();
	system("pause");
}

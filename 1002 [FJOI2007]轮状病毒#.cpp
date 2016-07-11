#include <cstdio>
#include <cstdlib>
#include <cstring>
#define situ_size 3
#define Base 10000
#define Huge_Num_size 1000
const int f1[situ_size]={1,0,1};
const int opt[situ_size][situ_size]={
//        f[n-1] f[n-2] 1
/* f[n] */  3,     -1,  2,
/*f[n-1]*/  1,      0,  0,
/*  1   */  0,      0,  1};
int N;
inline int max(const int a,const int b) { return a>b?a:b; }
struct Huge_Num {
	int size;
	short a[Huge_Num_size];
	Huge_Num() {
		memset(a,0,Huge_Num_size*sizeof(a[0]));
	}
	void init() { Huge_Num(); }
	void init1(const short x) {
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
	}
};
Huge_Num* operator += (Huge_Num &a,const Huge_Num &b) {
	int i,carry=0;
	a.size=max(a.size,b.size);
	for (i=0;i<a.size;++i) {
		carry+=a.a[i]+b.a[i];
		a.a[i]=carry%Base;
		carry/=Base;
	}
	if (carry) a.a[a.size++]=carry;
	return &a;
}
Huge_Num operator * (const Huge_Num &a,const Huge_Num &b) {
	Huge_Num c;
	int i,j,k,carry=0;
	for (j=0;j<b.size;++j) {
		for (i=0,k=j;i<a.size;++i,++k) {
			carry+=a.a[i]+b.a[j]+c.a[k];
			c.a[k]=carry%Base;
			carry/=Base;
		}
		while (carry) {
			carry+=c.a[k];
			c.a[k++]=carry%Base;
			carry/=Base;
		}
	}
	while (c.a[c.size++]);
	return c;
}
typedef Huge_Num Situ[situ_size];
Situ situ,situ_;
typedef Huge_Num Matrix[situ_size][situ_size];
Matrix matrix,matrix_;
void p(int x) {
	int i,j;
	printf("\n");
	if (x&2) {
	for (i=0;i<situ_size;++i) situ[i].print(),printf("%c",i<situ_size-1?' ':'\n');
	printf("\n"); }
	if (x&1) {
	for (i=0;i<situ_size;++i)
		for (j=0;j<situ_size;++j)
			matrix[i][j].print(),printf("%c",j<situ_size-1?' ':'\n');
	printf("\n"); }
}
void init() {
	int i,j;
	for (i=0;i<situ_size;++i) situ[i].init1(f1[i]);
	for (i=0;i<situ_size;++i)
		for (j=0;j<situ_size;++j)
			matrix[i][j].init1(opt[i][j]);
}
void operat() {
	int i,j;
	for (i=0;i<situ_size;++i) {
		situ_[i].init();
		for (j=0;j<situ_size;++j)
			situ_[i]+=matrix[i][j]*situ[j];
	}
	memcpy(situ,situ_,sizeof(situ));
	p(2);
}
void sqri() {
	int i,j,k;
	for (i=0;i<situ_size;++i)
		for (j=0;j<situ_size;++j) {
			matrix_[i][j].init();
			for (k=0;k<situ_size;++k)
				matrix_[i][j]+=matrix[i][k]*matrix[k][j];
		}
	memcpy(matrix,matrix_,sizeof(matrix));
	p(1);
}
void Power(unsigned sum) {
	for (;sum;sum>>=1,sqri())
		if (sum&1) operat();
}
int main() {
	scanf("%d",&N);
	init();
	Power(N-1);
	situ[0].print();
	printf("\n");
	system("pause");
}

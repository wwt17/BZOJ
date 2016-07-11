#include <cstdio>
#define size 1001
int N,i,a,b,c;
short v[size],x,y;
bool f[size];
short belong(int k) {
	if (v[k]==k) return k;
	short tmp=v[k];
	v[k]=belong(v[k]);
	f[k]^=f[tmp];
	return v[k];
}
int main() {
	scanf("%d",&N);
	for (i=1;i<=N;++i) v[i]=i;
	for (i=1;i<N;++i) {
		scanf("%d%d%d",&a,&b,&c);
		x=belong(a);
		y=belong(b);
		v[y]=x;
		f[y]=f[a]^c^f[b];
	}
	x=belong(N);
	printf("%d\n",f[N]);
}

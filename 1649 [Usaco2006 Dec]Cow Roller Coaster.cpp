#include <cstdio>
#include <cstring>
#include <algorithm>
int L,N,B,i,j,f[1001][1001];
void maxi(int &a,int b) { if (a<b) a=b; }
struct interval {
	int X,W,F,C;
	void read() {
		scanf("%d%d%d%d",&X,&W,&F,&C);
		W+=X;
	}
	void work() {
		for (j=C;j<=B;++j) {
			maxi(f[X][j],f[W][j-C]+F);
		}
	}
};
inline bool cmp(const interval &a,const interval &b) {
	return a.X>b.X;
}
int main() {
	scanf("%d%d%d",&L,&N,&B);
	interval s[N];
	for (i=0;i<N;++i) s[i].read();
	std::sort(s,s+N,cmp);
	memset(f,0x80,sizeof(f));
	memset(f[L],0,sizeof(f[L]));
	for (int t=0;t<N;++t)
		s[t].work();
	printf("%d\n",f[0][B]<0?-1:f[0][B]);
	system("pause");
}

#include <cstdio>
#include <algorithm>
using namespace std;
#define inf 2000000000
int N,i,f1,f2,f3;
inline void work(const int &d) {
	f3=min(min(f1,f2),f3)+1; f2=min(f1,f2)+1; ++f1;
	switch(d) {
		case 1: --f1; break;
		case 2: --f2; break;
		case 3: --f3; break;
	}
}
int main() {
	scanf("%d",&N);
	int D[N],tmp;
	for (i=0;i<N;++i) scanf("%d",&D[i]);
	f1=0,f2=f3=inf;
	for (i=0;i<N;++i) work(D[i]);
	tmp=min(min(f1,f2),f3);
	f1=0,f2=f3=inf;
	for (i=N-1;i>=0;--i) work(D[i]);
	printf("%d\n",min(tmp,min(min(f1,f2),f3)));
	system("pause");
}

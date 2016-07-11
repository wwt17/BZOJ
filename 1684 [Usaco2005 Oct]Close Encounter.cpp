#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define inf 0x7fffffff
#define bound 32768
int A,B,X,Y,x,y;
double num,Dist=inf,dist;
inline double abs(const double x) {
	if (x<0) return -x; return x;
}
inline void Try() {
	if (A*y==B*x) return;
	if (Dist>(dist=abs((double)x/y-num)))
		X=x,Y=y,Dist=dist;
}
int main() {
	scanf("%d%d",&A,&B);
	num=(double)A/B;
	for (y=1;y<bound;++y) {
		x=(int)(num*y);
		Try();
		++x;
		Try();
	}
	printf("%d %d\n",X,Y);
	system("pause");
}

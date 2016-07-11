#include <cstdio>
#include <cstdlib>
#define size 200
#define sizexy 2002
int N,i,j,X[size],Y[size],g,x,y,a,b,ans;
bool f[sizexy*2][sizexy*2],t;
int gcd(int a,int b) {
	if (!b) return a;
	return gcd(b,a%b);
}
int main() {
	scanf("%d",&N);
	for (i=0;i<N;++i) {
		scanf("%d%d",&X[i],&Y[i]);
		for (j=0;j<i;++j) {
			x=X[i]-X[j];
			y=Y[i]-Y[j];
			t=false;
			if (x<0) t=!t,x=-x;
			if (y<0) t=!t,y=-y;
			g=gcd(x,y);
			x/=g;
			y/=g;
			if (t) y=-y;
			if (!x) y=0;
			x+=sizexy;
			y+=sizexy;
			if (!f[x][y]) ++ans,f[x][y]=true;
		}
	}
	printf("%d\n",ans);
	system("pause");
}

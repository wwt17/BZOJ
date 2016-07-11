#include <stdio.h>
#include <stdlib.h>
#define size 10000
int n,m,i,j,ans;
struct situ {
	int time,x,y,f;
	void read() {
		scanf("%d%d%d",&time,&x,&y);
	}
} a[size];
inline void maxi(int &a,int b) { a<b?a=b:0; }
int main() {
	scanf("%d%d",&n,&m);
	for (i=0;i<m;++i) {
		a[i].read();
		for (j=i-1;j>=0;--j)
			if (abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y)<=(a[i].time-a[j].time))
				maxi(a[i].f,a[j].f);
		maxi(ans,++a[i].f);
	}
	printf("%d\n",ans);
}

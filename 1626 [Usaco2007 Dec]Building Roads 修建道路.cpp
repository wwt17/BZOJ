#include<cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
#define size 1001
#define maxint 0x7fffffff
#define P 100
int N,M,i,j,X[size],Y[size],t[size],d[size][size],v[size],x,y;
double graph[size][size],ans;
inline double sqr(long double x) { return x*x; }
inline bool cmp(int a,int b) { return graph[i][a]<graph[i][b]; }
inline double line(int x) { return graph[x][d[x][d[x][0]]]; }
void down(int i) {
	for (int j;i<=(t[0]>>1);i=j) {
		j=i<<1;
		if (j+1<=N&&line(t[j+1])<line(t[j])) ++j;
		if (line(t[i])>line(t[j])) { int tmp=t[i];t[i]=t[j];t[j]=tmp; }
		else break;
	}
}
inline int belong (int k) {
	if (k==v[k]) return k;
	return v[k]=belong(v[k]);
}
int main() {
	scanf("%d%d\n",&N,&M);
	for (i=1;i<=N;++i) {
		scanf("%d%d\n",&X[i],&Y[i]);
		for (j=1;j<i;++j)
		  graph[i][j]=graph[j][i]=sqrt(sqr((double)(X[i]-X[j])/P)+sqr((double)(Y[i]-Y[j])/P))*P;
		graph[i][i]=0;
	}
	for (;M;--M) {
		scanf("%d%d\n",&i,&j);
		graph[i][j]=graph[j][i]=0;
	}
	t[0]=N;
	for (i=1;i<=N;++i) {
		d[i][0]=1;
		for (j=1;j<=N;++j) d[i][j]=j;
		sort(d[i]+1,d[i]+N+1,cmp);
		t[i]=i;
	}
	for (i=(t[0]>>1);i;--i) down(i);
	for (i=1;i<=N;++i) v[i]=i;
	for (i=N-1;i;) {
		x=belong(t[1]);
		y=belong(d[t[1]][d[t[1]][0]]);
		if (x!=y) {
			ans+=line(t[1]);
			v[y]=x;
			--i;
		}
		++d[t[1]][0];
		if (d[t[1]][0]>N) t[1]=t[t[0]--];
		down(1);
	}
	printf("%.2f\n",ans);
}

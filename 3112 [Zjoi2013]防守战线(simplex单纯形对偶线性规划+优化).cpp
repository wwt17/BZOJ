#include <cstdio>

const int N=1005,M=10005,inf=1e9;

int n,m,cnt,a[N][M],p[M],q[M];

inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}

void pivot(int x,int y){
	cnt=0;
	for(int j=0;j<=m;j++) if(j!=y&&a[x][j]){
		p[cnt]=j; q[cnt++]=a[x][j];
	}
	for(int i=0;i<=n;i++) if(i!=x){
		int z=a[i][y];
		for(int j=0;j<cnt;j++) a[i][p[j]]-=z*q[j];
		a[i][y]*=-1;
	}
}

int simplex(){
	while(1){
		int x=0,y=0,best=0;
		for(int j=1;j<=m;j++) if(a[0][j]>best){
			best=a[0][j];
			y=j;
		}
		if(!y) return -a[0][0];
		best=inf;
		for(int i=1;i<=n;i++) if(a[i][y]>0&&a[i][0]<best){
			best=a[i][0];
			x=i;
		}
		if(!x) return inf;
		pivot(x,y);
	}
}

int main(){
	n=getint(),m=getint();
	for(int i=1;i<=n;i++) a[i][0]=getint();
	for(int j=1;j<=m;j++){
		int l=getint(),r=getint();
		for(int i=l;i<=r;i++) a[i][j]=1;
		a[0][j]=getint();
	}
	printf("%d\n",simplex());
}

#include <cstdio>
#include <algorithm>
using namespace std;
const int N=2048;
int n,m;
int map[N][N],a[N][N],b[N][N],l[N][N],r[N][N],u[N][N],d[N][N];
struct data{
	int loc,h;
} q[N],*head,*tail;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n*2;i++)
		for(int j=0;j<=m*2;j++)
			if(i&1&&j&1) scanf("%d",&map[i][j]);
			else map[i][j]=-1;
	
	int k;
	/*
	for(int i=0;i<=n*2;puts(""),i++)
		for(int j=0;j<=m*2;map[i][j]==-1?printf(" ."):printf("%2d",map[i][j]),j++);
	puts("");
	*/
	for(int i=0;i<=n*2;i++)
		for(int j=0,r=0;j<=m*2;){
			while(j-r-1>=0&&j+r+1<=m*2&&map[i][j-r-1]==map[i][j+r+1]) r++;
			a[i][j]=r;
			for(k=1;k<=r&&a[i][j-k]!=r-k;k++) a[i][j+k]=min(a[i][j-k],r-k);
			j+=k;
			r=max(0,r-k);
		}
	for(int j=0;j<=m*2;j++)
		for(int i=0,r=0;i<=n*2;){
			while(i-r-1>=0&&i+r+1<=n*2&&map[i-r-1][j]==map[i+r+1][j]) r++;
			b[i][j]=r;
			for(k=1;k<=r&&b[i-k][j]!=r-k;k++) b[i+k][j]=min(b[i-k][j],r-k);
			i+=k;
			r=max(0,r-k);
		}
	
	for(int i=0;i<=n*2;i++){
		head=tail=q;
		for(int j=0,k=0;j<=m*2;j++){
			int loc=j,h=b[i][j];
			while(head<tail&&tail[-1].h>h) loc=(--tail)->loc;
			*tail++=(data){loc,h};
			*tail=(data){j,N};
			while(k<head[0].loc) k++;
			while(head[0].h<j-k)
				if(head[1].loc==++k) head++;
			l[i][j]=j-k;
		}
		head=tail=q;
		for(int j=m*2,k=m*2;j>=0;j--){
			int loc=j,h=b[i][j];
			while(head<tail&&tail[-1].h>h) loc=(--tail)->loc;
			*tail++=(data){loc,h};
			*tail=(data){j,N};
			while(k>head[0].loc) k--;
			while(head[0].h<k-j)
				if(head[1].loc==--k) head++;
			r[i][j]=k-j;
		}
	}
	/*
	for(int i=0;i<=n*2;puts(""),i++)
		for(int j=0;j<=m*2;printf("%2d",l[i][j]),j++);
	puts("");
	*/
	for(int j=0;j<=m*2;j++){
		head=tail=q;
		for(int i=0,k=0;i<=n*2;i++){
			int loc=i,h=a[i][j];
			while(head<tail&&tail[-1].h>h) loc=(--tail)->loc;
			*tail++=(data){loc,h};
			*tail=(data){i,N};
			while(k<head[0].loc) k++;
			while(head[0].h<i-k)
				if(head[1].loc==++k) head++;
			u[i][j]=i-k;
		}
		head=tail=q;
		for(int i=n*2,k=n*2;i>=0;i--){
			int loc=i,h=a[i][j];
			while(head<tail&&tail[-1].h>h) loc=(--tail)->loc;
			*tail++=(data){loc,h};
			*tail=(data){i,N};
			while(k>head[0].loc) k--;
			while(head[0].h<k-i)
				if(head[1].loc==--k) head++;
			d[i][j]=k-i;
		}
	}
	/*
	for(int i=0;i<=n*2;puts(""),i++)
		for(int j=0;j<=m*2;printf("%2d",u[i][j]),j++);
	puts("");
	*/
	int ans=0;
	for(int i=0;i<=n*2;i++)
		for(int j=0;j<=m*2;j++)
			if(!((i^j)&1))
				ans+=(i&1)+min(min(l[i][j],r[i][j]),min(u[i][j],d[i][j]))/2;
	printf("%d\n",ans);
	scanf("\n");
}

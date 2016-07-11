#include <cstdio>
const int N=1005;
int q,n,m,a,b,cnt,t[N*N][2];
char f[N][N],g[N][N];
bool work(){
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=0;i<n;i++)
		scanf("%s",f[i]);
	cnt=0;
	for(int i=0;i<a;i++){
		scanf("%s",g[i]);
		for(int j=0;j<b;j++) if(g[i][j]=='x'){
			t[cnt][0]=i;
			t[cnt][1]=j;
			cnt++;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++) if(f[i][j]=='x')
			for(int k=0;k<cnt;k++){
				int	x=i-t[0][0]+t[k][0],
					y=j-t[0][1]+t[k][1];
				if(x<0||x>=n||y<0||y>=m||f[x][y]=='.')
					return 0;
				f[x][y]='.';
			}
	return 1;
}
int main(){
	scanf("%d",&q);
	while(q--)
		puts(work()?"TAK":"NIE");
}

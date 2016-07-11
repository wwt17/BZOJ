#include <cstdio>
const int N=5,BND=16;
const int dir[8][2]={ {-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2} };
char a[N+1][N+1];
char b[N+1][N+1];
int bnd,nbnd,gu;
bool ok;
void dfs(int x,int y,int step){
	if(step+gu>bnd){
		if(step+gu<nbnd) nbnd=step+gu;
		return;
	}
	if(gu==0){
		ok=1;
		return;
	}
	for(int d=0;d<8;d++){
		int xx=x+dir[d][0],yy=y+dir[d][1];
		if(xx<0||xx>=N||yy<0||yy>=N) continue;
		if(a[xx][yy]!=b[xx][yy]) gu--;
		a[x][y]=a[xx][yy];
		if(a[x][y]!=b[x][y]) gu++;
		dfs(xx,yy,step+1);
		if(a[x][y]!=b[x][y]) gu--;
		a[xx][yy]=a[x][y];
		if(a[xx][yy]!=b[xx][yy]) gu++;
		if(ok) return;
	}
}
int work(){
	int x,y;
	for(int i=0;i<N;i++) scanf("%s",a[i]);
	gu=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++){
			b[i][j]=j<i?'0':j>i?'1':i<2?'1':i>2?'0':'*';
			if(a[i][j]=='*'){
				x=i,y=j;
				continue;
			}
			if(a[i][j]!=b[i][j]) gu++;
		}
	bnd=gu;
	ok=0;
	for(;bnd<BND;bnd=nbnd){
		nbnd=BND;
		dfs(x,y,0);
		if(ok) return bnd;
	}
	return -1;
}
int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",work());
}

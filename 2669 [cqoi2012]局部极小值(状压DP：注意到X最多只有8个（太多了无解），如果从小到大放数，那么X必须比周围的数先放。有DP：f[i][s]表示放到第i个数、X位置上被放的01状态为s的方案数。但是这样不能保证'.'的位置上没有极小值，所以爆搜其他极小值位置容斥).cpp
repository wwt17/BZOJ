#include <cstdio>
#include <cstdlib>
const int N=4,M=7,C=8,mo=12345678;
int n,m;
char a[N][M+1];
int top,t[C][2],f[N*M+1][1<<C],cnt[1<<C];
int work(){
	top=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(a[i][j]=='X')
				t[top][0]=i,t[top][1]=j,top++;
	for(int i=0;i<=n*m;i++)
		for(int s=0;s<1<<top;s++) f[i][s]=0;
	for(int s=0;s<1<<top;s++){
		cnt[s]=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++) if(a[i][j]!='X'){
				bool ok=true;
				for(int k=0;k<top;k++) if(abs(t[k][0]-i)<=1&&abs(t[k][1]-j)<=1&&!(s>>k&1)){
					ok=false;
					break;
				}
				cnt[s]+=ok;
			}
	}
	f[0][0]=1;
	for(int i=0;i<n*m;i++){
		for(int s=0;s<1<<top;s++){
			int tmp=0;
			for(int j=0;j<top;j++) if(!(s>>j&1)){
				(f[i+1][s|1<<j]+=f[i][s])%=mo;
			}
			else
				tmp++;
			(f[i+1][s]+=1LL*f[i][s]*(cnt[s]-(i-tmp))%mo)%=mo;
		}
	}
	return f[n*m][(1<<top)-1];
}
int dfs(int i,int j){
	if(j==m){
		if(i==n-1)
			return work();
		else
			return dfs(i+1,0);
	}
	if(a[i][j]=='X')
		return dfs(i,j+1);
	else{
		int tmp=dfs(i,j+1);
		for(int x=i-1;x<=i+1;x++)
			for(int y=j-1;y<=j+1;y++) if(x>=0&&x<n&&y>=0&&y<m&&a[x][y]=='X')
				return tmp;
		a[i][j]='X';
		(tmp-=dfs(i,j+1))%=mo;
		a[i][j]='.';
		return tmp;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",a[i]);
	printf("%d\n",(dfs(0,0)+mo)%mo);
}

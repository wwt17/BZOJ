#include <cstdio>
const int N=505,inf=(int)1e9;
void mini(int &a,const int b){
	if(b<a) a=b;
}
int n,m,a[N],b[N],f[N][N];
int main(){
	scanf("%d",&m);
	while(m--){
		int x; scanf("%d",&x);
		if(n&&x==a[n]) b[n]++;
		else a[++n]=x,b[n]=1;
	}
	for(int i=n;i;i--){
		f[i][i]=b[i]==1?2:1;
		for(int j=i+1;j<=n;j++){
			f[i][j]=inf;
			for(int k=i;k<j;k++)
				mini(f[i][j],f[i][k]+f[k+1][j]);
			if(a[i]==a[j]){
				mini(f[i][j],f[i+1][j-1]+(b[i]+b[j]==2?1:0));
				for(int k=i+1;k<j;k++) if(a[k]==a[i])
					mini(f[i][j],f[i+1][k-1]+f[k+1][j-1]);
			}
		}
	}
	printf("%d\n",f[1][n]);
}

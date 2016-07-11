#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=0x7fffffff;
char s[51];
int n,f[50][50][26],g[50][50];
inline void mini(int &a,const int b){
	if(a>b) a=b;
}
int main(){
	scanf("%s",s); n=strlen(s);
	for(int i=0;s[i];i++) s[i]-='A';
	for(int i=n-1;i>=0;i--){
		for(int c=0;c<26;c++) f[i][i][c]=s[i]!=c; g[i][i]=0;
		for(int j=i+1;j<n;j++){
			g[i][j]=inf;
			for(int c=0;c<26;c++){
				f[i][j][c]=inf;
				for(int k=i;k<j;k++)
					mini(f[i][j][c],min(g[i][k]+1,f[i][k][c])+min(g[k+1][j]+1,f[k+1][j][c]));
				mini(g[i][j],f[i][j][c]);
			}
		}
	}
	int ans=inf;
	for(int c=0;c<26;c++) mini(ans,f[0][n-1][c]+1);
	printf("%d\n",ans);
}

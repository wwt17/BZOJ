#include <cstdio>
const int N=51,M=3;
int len[M];
char s[M][N];
int main(){
	for(int j=0;j<M;j++){
		scanf("%d",&len[j]);
		if(len[j]) scanf("%s",s[j]);
	}
	int ans=1e8;
	for(int jj=0;jj<M;jj++)
		for(int ii=0;ii<=len[jj];ii++){
			int cur=0;
			for(int j=0;j<M;j++){
				int i=0;
				for(;i<len[j]&&i<ii&&s[j][i]==s[jj][i];i++);
				cur+=len[j]-i+ii-i;
			}
			if(cur<ans) ans=cur;
		}
	printf("%d\n",ans);
}

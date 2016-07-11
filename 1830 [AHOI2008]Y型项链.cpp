#include <cstdio>
const int N=55,M=3;
int len[M];
char s[M][N],t[N];
int main(){
	for(int j=0;j<M;j++){
		scanf("%d",&len[j]);
		if(len[j]) scanf("%s",s[j]);
	}
	int ans=0x7fffffff;
	for(int jj=0;jj<M;jj++)
		for(int ii=0;ii<=len[jj];ii++){
			int cur=0;
			for(int j=0;j<M;j++){
				int dif=0;
				for(;dif<len[j]&&dif<ii&&s[j][dif]==s[jj][dif];dif++);
				cur+=len[j]-dif+ii-dif;
			}
			if(cur<ans) ans=cur;
		}
	printf("%d\n",ans);
	scanf("\n");
}

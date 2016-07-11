#include <cstdio>

const int N=40005;

int n;
char s[10];
int num[4];
bool g[52][52];

int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%s",s);
		for(int i=0;i<4;i++){
			if(s[i<<1]=='0'){
				num[i]=-1;
				continue;
			}
			num[i]=(s[i<<1]-'A')<<1|(s[i<<1|1]=='-');
		}
		for(int i=0;i<4;i++) if(num[i]!=-1)
			for(int j=0;j<4;j++) if(num[j]!=-1) if(i!=j){
				g[num[i]^1][num[j]]=true;
			}
	}
	for(int k=0;k<52;k++)
		for(int i=0;i<52;i++) if(g[i][k])
			for(int j=0;j<52;j++) if(g[k][j])
				g[i][j]=true;
	bool unbounded=false;
	for(int i=0;i<52;i++) unbounded|=g[i][i];
	puts(unbounded?"unbounded":"bounded");
}

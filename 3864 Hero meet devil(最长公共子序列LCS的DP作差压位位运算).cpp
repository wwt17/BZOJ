#include <cstdio>

const int N=15,M=1005,mo=(int)1e9+7;
const char dic[]="ACGT";

inline void inc(int &a,const int b){
	if((a+=b)>=mo) a-=mo;
}

int n,m;
char s[N+1];
int b[4];
int nex[1<<N][4];
int f[M][1<<N];
int cnt1[1<<N];
int ans[N+1];

void Main(){
	scanf("%s%d",s,&m);
	for(n=0;s[n];n++);
	for(int c=0;c<4;c++){
		b[c]=0;
		for(int i=0;i<n;i++) if(dic[c]==s[i]) b[c]|=1<<i;
	}
	for(int i=0;i<1<<n;i++)
		for(int c=0;c<4;c++){
			int x=i|b[c];
			nex[i][c]=((x-(i<<1|1))^x)&x;
		}
	f[0][0]=1;
	for(int j=1;j<=m;j++){
		for(int i=0;i<1<<n;i++) f[j][i]=0;
		for(int i=0;i<1<<n;i++)
			for(int c=0;c<4;c++)
				inc(f[j][nex[i][c]],f[j-1][i]);
	}
	for(int i=0;i<=n;i++) ans[i]=0;
	for(int i=0;i<1<<n;i++){
		cnt1[i]=cnt1[i>>1]+(i&1);
		inc(ans[cnt1[i]],f[m][i]);
	}
	for(int i=0;i<=n;i++) printf("%d\n",ans[i]);
}

int main(){
	int T; scanf("%d",&T);
	while(T--) Main();
	scanf("\n");
}

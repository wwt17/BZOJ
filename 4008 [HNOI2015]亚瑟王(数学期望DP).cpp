#include <cstdio>

typedef double db;

const int N=230,R=140;

int n,r;

db p[N];
int d[N];
db pw[N][R],f[N][R];

db Main(){
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++){
		scanf("%lf%d",&p[i],&d[i]);
		pw[i][0]=1;
		for(int j=1;j<=r;j++)
			pw[i][j]=pw[i][j-1]*(1-p[i]);
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=r;j++)
			f[i][j]=0;
	f[0][r]=1;
	db ans=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=r;j++){
			ans+=f[i-1][j]*(1-pw[i][j])*d[i];
			f[i][j]+=f[i-1][j]*pw[i][j];
			if(j) f[i][j-1]+=f[i-1][j]*(1-pw[i][j]);
		}
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%.10lf\n",(double)Main());
}

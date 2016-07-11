#include <cstdio>
const int N=10,M=10,inf=(int)1e9;
int n,m,F,ans,val,a[N+1][M+1],b[N+1][M+1],f[2][1<<(M+2)*2];
char flag[1<<(M+2)*2];
int cnts,level,stack[M+2],sta[16000],mat[16000][M+2];
bool ok[N+1][M+1];
void renew(int &a){
	if(val>a) a=val;
}
int main(){
	scanf("%d%d",&n,&m);
	int po=1;
	for(int j=0;j<m+2;j++) po*=3;
	for(int t=0;t<po;t++){
		int s=0;
		for(int tt=t,j=0;j<m+2;tt/=3,j++) s|=tt%3<<j*2;
		level=0;
		bool ok=1;
		for(int j=0;j<m+2;j++){
			if((s>>j*2&3)==1)
				stack[level++]=j;
			else
			if((s>>j*2&3)==2){
				if(!level){
					ok=0;
					break;
				}
				level--;
				mat[cnts][stack[level]]=j;
				mat[cnts][j]=stack[level];
			}
		}
		if(ok) flag[s]=level;
		if(level) ok=0;
		if(ok) sta[cnts++]=s;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	ans=-inf;
	for(int ss=0;ss<cnts;ss++) f[F][sta[ss]]=f[F^1][sta[ss]]=-inf;
	f[F][0]=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int ss=0;ss<cnts;ss++){
				int s=sta[ss],t=s&~(15<<j*2),x=s>>j*2&3,y=s>>(j+1)*2&3;
				val=f[F][s]+(flag[s&(1<<(j+1)*2)-1]&1?a[i][j]:0);
				switch(x){
					case 0:
						if(y){
							renew(f[!F][t|y<<j*2]);
							renew(f[!F][t|y<<(j+1)*2]);
						}
						else{
							renew(f[!F][t]);
							renew(f[!F][t|9<<j*2]);
						}
						break;
					case 1:
						switch(y){
							case 0:
								renew(f[!F][t|1<<j*2]);
								renew(f[!F][t|1<<(j+1)*2]);
								break;
							case 1:
								renew(f[!F][t^3<<mat[ss][j+1]*2]);
								break;
							case 2:
								if(!t)
									renew(ans);
								break;
						}
						break;
					case 2:
						switch(y){
							case 0:
								renew(f[!F][t|2<<j*2]);
								renew(f[!F][t|2<<(j+1)*2]);
								break;
							case 1:
								renew(f[!F][t]);
								break;
							case 2:
								renew(f[!F][t^3<<mat[ss][j]*2]);
								break;
						}
						break;
				}
				f[F][s]=-inf;
			}
			F^=1;
		}
		for(int ss=0;ss<cnts;ss++){
			int s=sta[ss];
			if((s>>(m+1)*2)==0)
				val=f[F][s],renew(f[F^1][s<<2]);
			f[F][s]=-inf;
		}
		F^=1;
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	bool fine=1;
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--){
			ok[i][j]=fine;
			fine&=b[i][j]!=2;
		}
	ans=-inf;
	for(int ss=0;ss<cnts;ss++) f[F][sta[ss]]=f[F^1][sta[ss]]=-inf;
	f[F][0]=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int ss=0;ss<cnts;ss++){
				int s=sta[ss],t=s&~(15<<j*2),x=s>>j*2&3,y=s>>(j+1)*2&3;
				val=f[F][s]+(flag[s&(1<<(j+1)*2)-1]&1?a[i][j]:0);
				if(	b[i][j]==1&&flag[s&(1<<(j+1)*2)-1]&1
				||	b[i][j]==2&&!(flag[s&(1<<(j+1)*2)-1]&1)) val=-inf;
				switch(x){
					case 0:
						if(y){
							renew(f[!F][t|y<<j*2]);
							renew(f[!F][t|y<<(j+1)*2]);
						}
						else{
							renew(f[!F][t]);
							renew(f[!F][t|9<<j*2]);
						}
						break;
					case 1:
						switch(y){
							case 0:
								renew(f[!F][t|1<<j*2]);
								renew(f[!F][t|1<<(j+1)*2]);
								break;
							case 1:
								renew(f[!F][t^3<<mat[ss][j+1]*2]);
								break;
							case 2:
								if(!t&&ok[i][j])
									renew(ans);
								break;
						}
						break;
					case 2:
						switch(y){
							case 0:
								renew(f[!F][t|2<<j*2]);
								renew(f[!F][t|2<<(j+1)*2]);
								break;
							case 1:
								renew(f[!F][t]);
								break;
							case 2:
								renew(f[!F][t^3<<mat[ss][j]*2]);
								break;
						}
						break;
				}
				f[F][s]=-inf;
			}
			F^=1;
		}
		for(int ss=0;ss<cnts;ss++){
			int s=sta[ss];
			if((s>>(m+1)*2)==0)
				val=f[F][s],renew(f[F^1][s<<2]);
			f[F][s]=-inf;
		}
		F^=1;
	}
	if(ans<-5e8)
		puts("Can not establish GFW.");
	else
		printf("%d\n",ans);
}

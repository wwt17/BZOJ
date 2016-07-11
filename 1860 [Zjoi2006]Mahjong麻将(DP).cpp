#include <cstdio>
const int n=100;
int mem[n+2],*a=mem+2;
bool f[2][7][7][2],F;
inline bool check(int x,int y){
	return ! ( x<y || x-y==1 || x-y==2 || x-y==5 );
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		for(int j=0;j<7;j++)
			for(int k=0;k<7;k++)
				f[F][j][k][0]=f[F][j][k][1]=false;
		f[F][0][0][0]=true;
		for(int i=0;i<n;i++){
			scanf("%u",a+i);
			for(int j=0;j<7;j++) if(a[i-1]>=j)
				for(int k=0;k<7;k++) if(a[i]>=k){
					f[!F][j][k][0]=f[!F][j][k][1]=false;
					if(k>=2) f[!F][j][k][1]|=f[!F][j][k-2][0];
					if(j>=k) for(int l=k;l<7;l++) if(check(a[i-2],l))
						f[!F][j][k][0]|=f[F][l-k][j-k][0],
						f[!F][j][k][1]|=f[F][l-k][j-k][1];
				}
			F^=1;
		}
		bool win=false;
		for(int j=0;j<7;j++) if(check(a[n-2],j))
			for(int k=0;k<7;k++) if(check(a[n-1],k))
				win|=f[F][j][k][1];
		puts(win?"Yes":"No");
	}
}

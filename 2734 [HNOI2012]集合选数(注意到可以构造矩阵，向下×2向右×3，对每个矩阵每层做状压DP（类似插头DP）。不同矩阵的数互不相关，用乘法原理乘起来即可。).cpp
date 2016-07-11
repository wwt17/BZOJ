#include <cstdio>
const int N=100005,S=20,mo=(int)1e9+1;
int n;
long long ans=1;
bool done[N];
int a[S][S];
int w,f[1<<S],g[1<<S];
inline void inc(int &a,const int b){
	if((a+=b)>=mo) a-=mo;
}
int main(){
	scanf("%d",&n);
	for(int d=1;d<=n;d++) if(!done[d]){
		a[0][0]=d;
		for(int i=1;;i++){
			a[i][0]=a[i-1][0]*2;
			if(a[i][0]>n) break;
		}
		for(int i=0;a[i][0]<=n;i++){
			for(int j=1;;j++){
				a[i][j]=a[i][j-1]*3;
				if(a[i][j]>n) break;
			}
		}
		for(int i=0;a[i][0]<=n;i++)
			for(int j=0;a[i][j]<=n;j++)
				done[a[i][j]]=true;
		for(w=0;a[0][w]<=n;w++);
		for(int s=0;s<1<<w;s++) f[s]=g[s]=0;
		f[0]=1;
		for(int i=0;a[i][0]<=n;i++){
			int j;
			for(j=0;a[i][j]<=n;j++){
				for(int s=0;s<1<<w;s++){
					int t=s&~(1<<j);
					inc(g[t],f[s]);
					if((j==0||!(s>>(j-1)&1))&&!(s>>j&1))
						inc(g[t|1<<j],f[s]);
				}
				for(int s=0;s<1<<w;s++) f[s]=g[s],g[s]=0;
			}
			for(int s=0;s<1<<w;s++){
				int t=s&((1<<j)-1);
				inc(g[t],f[s]);
			}
			w=j;
			for(int s=0;s<1<<w;s++) f[s]=g[s],g[s]=0;
		}
		int now=0;
		for(int s=0;s<1<<w;s++) inc(now,f[s]);
		ans=ans*now%mo;
	}
	printf("%d\n",int(ans));
}

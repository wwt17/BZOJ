#include <cstdio>
int t,n,m,f[250];
inline int sg(int i,int j){
	if(i&&j) return i+j;
	int cnt=0;
	for(int k=i+j+1;!(k&1);k>>=1) cnt++;
	return cnt;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n+m;i++) f[i]=0;
		for(int i=0;i<n;i++){
			scanf("\n");
			for(int j=0;j<m;j++)
				if(getchar()!='H')
					f[sg(i,j)]^=1;
		}
		bool win=false;
		for(int i=0;i<n+m;i++) if(f[i]){
			win=true;
			break;
		}
		puts(win?"-_-":"=_=");
	}
}

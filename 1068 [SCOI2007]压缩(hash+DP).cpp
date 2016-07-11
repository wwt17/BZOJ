#include <cstdio>
#include <cstring>
const int N=55,mo=(int)1e6+7;
int n;
char s[N];
int h[N],power[N],f[N][N];
inline void mini(int &a,const int b){
	if(b<a) a=b;
}
int calc(int l,int r){
	return ((h[l]-1LL*h[r]*power[r-l])%mo+mo)%mo;
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	power[0]=1;
	for(int i=1;i<=n;i++) power[i]=power[i-1]*26%mo;
	for(int i=n-1;i>=0;i--)
		h[i]=(s[i]-'a'+h[i+1]*26)%mo;
	memset(f,0x70,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			mini(f[i][i],f[i][j]+1);
			int k=i*2-j;
			if(k<=n&&calc(j,i)==calc(i,k))
				mini(f[k][j],f[i][j]+1);
		}
		for(int j=0;j<=i;j++)
			mini(f[i+1][j],f[i][j]+1);
	}
	int ans=1e9;
	for(int j=0;j<=n;j++) mini(ans,f[n][j]);
	printf("%d\n",ans);
}

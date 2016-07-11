#include <cstdio>
#include <cstring>
const int N=105,mo=10000007;
void mini(int &a,const int b){
	if(b<a) a=b;
}
char s[N];
int n,f[N][N],t[N],power[N];
int calc(int i,int k){
	return ((t[i]-1LL*power[k]*t[i+k])%mo+mo)%mo;
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	for(int i=n-1;i>=0;i--) t[i]=(s[i]-'A'+26*t[i+1])%mo;
	power[0]=1;
	for(int i=1;i<=n;i++) power[i]=power[i-1]*26%mo;
	for(int i=n-1;i>=0;i--)
		for(int j=i+1;j<=n;j++){
			f[i][j]=j-i;
			for(int k=i+1;k<j;k++)
				mini(f[i][j],f[i][k]+f[k][j]);
			for(int k=1;k<j-i;k++) if((j-i)%k==0){
				int h=calc(i,k);
				bool ok=1;
				for(int l=i;l<j;l+=k) if(calc(l,k)!=h){
					ok=0;
					break;
				}
				if(!ok) continue;
				int cnt=2;
				for(int t=(j-i)/k;t;t/=10) cnt++;
				mini(f[i][j],f[i][i+k]+cnt);
			}
		}
	printf("%d\n",f[0][n]);
}

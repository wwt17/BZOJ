#include <cstdio>
#include <algorithm>
using namespace std;
const int N=(int)1e6+5,mo=(int)1e9+7;
int n,k,dic[128],power2[N];
char s[N];
int f[N][3],g[N][3],sum[N][3];
int main(){
	dic['X']=0;
	dic['B']=1;
	dic['W']=2;
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	power2[0]=1;
	for(int i=1;i<=n;i++){
		power2[i]=power2[i-1]*2%mo;
		for(int j=0;j<=3;j++)
			sum[i][j]=sum[i-1][j];
		sum[i][dic[s[i]]]++;
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		int t=max(0,i-k);
		for(int j=1;j<=2;j++){
			if(i>=k*j&&sum[i][3-j]-sum[t][3-j]==0){
				if(i==k)
					g[i][j]=1;
				else
				if(dic[s[t]]==0)
					g[i][j]=(f[t-1][j-1]+g[t][j-1])%mo;
				else
				if(dic[s[t]]==3-j)
					g[i][j]=f[t][j-1];
			}
			f[i][j]=(f[i-1][j]*(s[i]=='X'?2:1)%mo+g[i][j])%mo;
		}
		f[i][0]=(f[i-1][0]*(s[i]=='X'?2:1)%mo-g[i][1])%mo;
		f[i][1]=(f[i][1]-g[i][2])%mo;
	}
	printf("%d\n",(f[n][2]+mo)%mo);
}

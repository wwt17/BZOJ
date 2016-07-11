// f[level][sum][mod]->f[level+1][sum+c][mod+c*10^(level+1)]
#include <cstdio>
#include <cstring>
const int L=20,S=163;
long long a,b,sum[L],f[L][S][S];
bool done[L][S][S];
inline int sumof(long long x){
	int ret=0;
	while(x) ret+=x%10,x/=10;
	return ret;
}
int s;
long long F(int level,int t,int m){
	long long &ans=f[level][t][m];
	if(done[level][t][m]) return ans;
	done[level][t][m]=true;
	ans=0;
	for(int c=0;c<=9&&c<=t;c++)
		ans+=F(level-1,t-c,((m-c*sum[level-1])%s+s)%s);
	return ans;
}
int main(){
	scanf("%lld%lld",&a,&b);
	int lv=0;
	sum[lv]=1;
	for(long long t=b+1;t;t/=10,lv++) sum[lv+1]=sum[lv]*10;
	long long ans=0;
	f[0][0][0]=1;
	int ss=S-1<lv*9?S-1:lv*9;
	for(s=1;s<=ss;s++){
		for(int i=0;i<=s;i++)
			for(int j=0;j<=s;j++)
				done[0][i][j]=true;
		for(long long x=b+1,level=1;x;x/=10,level++)
			for(int i=0;i<=s;i++)
				for(int j=0;j<=s;j++)
					done[level][i][j]=false;
		long long now=0;
		for(long long l=a-1,r=b+1,sl=sumof(l),sr=sumof(r),level=0;l!=r;l/=10,r/=10,level++){
			sl-=l%10;
			sr-=r%10;
			if(l/10==r/10){
				for(int c=l%10+1;c<=r%10-1;c++) if(s-sl-c>=0)
					now+=F(level,s-sl-c,(s-(l/10*10+c)*sum[level]%s)%s);
				break;
			}
			for(int c=l%10+1;c<=9;c++) if(s-sl-c>=0)
				now+=F(level,s-sl-c,(s-(l/10*10+c)*sum[level]%s)%s);
			for(int c=r%10-1;c>=0;c--) if(s-sr-c>=0)
				now+=F(level,s-sr-c,(s-(r/10*10+c)*sum[level]%s)%s);
		}
		ans+=now;
	}
	printf("%lld\n",ans);
}

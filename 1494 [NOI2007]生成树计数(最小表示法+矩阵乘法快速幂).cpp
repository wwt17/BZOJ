#include <cstdio>
const int mo=65521,K=5,S=52;
int k,s,sta[S],power[K+1],num[3125];
long long n;
unsigned O,opt[2][S][S],A,ans[2][S];
int cnt[K+1];
int calc(int n){
	if(n==0) return 1;
	int ans=1;
	for(int i=0;i<n-2;i++) ans*=n;
	return ans;
}
int main(){
	scanf("%d%lld",&k,&n);
	if(k>n-1){
		printf("%d\n",calc(n));
		return 0;
	}
	power[0]=1;
	for(int i=1;i<=k;i++) power[i]=power[i-1]*k;
	for(int x=0;x<power[k];x++){
		bool ok=1;
		for(int j=0;j<k;j++){
			int t=x/power[j]%k;
			if(t>j||x/power[t]%k!=t) ok=0;
		}
		if(!ok) continue;
		sta[num[x]=s++]=x;
	}
	for(int i=0;i<s;i++){
		int x=sta[i];
		for(int t=0;t<1<<k;t++){
			bool ok=1;
			for(int j=0;j<k;j++) cnt[j]=0;
			for(int j=0;j<k;j++) if(t>>j&1) cnt[x/power[j]%k]++;
			for(int j=0;j<k;j++) if(cnt[j]>1) ok=0;
			if(x/power[k-1]%k==k-1&&!cnt[x/power[k-1]%k]) ok=0;
			if(!ok) continue;
			int y=x;
			for(int j=0;j<k;j++) y+=power[j];
			for(int j=0;j<k;j++) if(cnt[j])
				for(int jj=0;jj<k;jj++) if(y/power[jj]%k==j+1)
					y-=(j+1)*power[jj];
			y=y*k%power[k];
			opt[O][num[x]][num[y]]++;
		}
		ans[A][i]=1;
		for(int j=0;j<k;j++) (ans[A][i]*=calc(cnt[j]))%=mo;
	}
	for(n-=k;n;n>>=1){
		if(n&1){
			for(int j=0;j<s;j++){
				ans[!A][j]=0;
				for(int i=0;i<s;i++)
					(ans[!A][j]+=ans[A][i]*opt[O][i][j])%=mo;
			}
			A^=1;
		}
		for(int i=0;i<s;i++)
			for(int j=0;j<s;j++){
				opt[!O][i][j]=0;
				for(int k=0;k<s;k++)
					(opt[!O][i][j]+=opt[O][i][k]*opt[O][k][j])%=mo;
			}
		O^=1;
	}
	printf("%d\n",ans[A][num[0]]);
}

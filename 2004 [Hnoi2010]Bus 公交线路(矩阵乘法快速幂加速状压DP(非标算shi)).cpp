#include <cstdio>
#include <algorithm>
using namespace std;
const int S=256,mo=30031;
int n,k,p,A,O,s,st[S],opt[2][S][S],ans[2][S];
#define get(x) lower_bound(st,st+s,x)-st
int main(){
	scanf("%d%d%d",&n,&k,&p);
	for(int i=0;i<1<<p;i++){
		int cnt=0;
		for(int j=0;j<p;j++) cnt+=i>>j&1;
		if(cnt!=k) continue;
		st[s++]=i;
	}
	for(int t=0;t<s;t++){
		int i=st[t];
		if(i>>(p-1)&1)
			opt[O][t][get((i^(1<<(p-1)))<<1)]++;
		else{
			for(int j=0;j<p;j++) if(i>>j&1)
				opt[O][t][get((i^(1<<j))<<1)]++;
		}
	}
	ans[A][get((1<<k)-1)]=1;
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
	printf("%d\n",ans[A][get((1<<k)-1)]);
}

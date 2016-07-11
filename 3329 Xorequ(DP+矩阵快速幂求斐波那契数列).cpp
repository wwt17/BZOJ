#include <cstdio>
typedef long long ll;
const ll P=1e9+7,PP=P*P;
const int B=63;
bool O,A;
ll n,f[B]={1,2},opt[2][2][2],ans[2][2];
inline ll mul(ll a,ll b){
	ll ans=0;
	for(;b;b>>=1,a=(a<<1)%PP)
		if(b&1) ans=(ans+a)%PP;
	return ans;
}
inline void mulopt(){
	opt[!O][0][0]=(opt[O][0][0]*opt[O][0][0]+opt[O][0][1]*opt[O][1][0])%P;
	opt[!O][0][1]=(opt[O][0][0]*opt[O][0][1]+opt[O][0][1]*opt[O][1][1])%P;
	opt[!O][1][0]=(opt[O][1][0]*opt[O][0][0]+opt[O][1][1]*opt[O][1][0])%P;
	opt[!O][1][1]=(opt[O][1][0]*opt[O][0][1]+opt[O][1][1]*opt[O][1][1])%P;
	O^=1;
}
inline void mulans(){
	ans[!A][0]=(ans[A][0]*opt[O][0][0]+ans[A][1]*opt[O][1][0])%P;
	ans[!A][1]=(ans[A][0]*opt[O][0][1]+ans[A][1]*opt[O][1][1])%P;
	A^=1;
}
int main(){
	for(int i=2;i<B;i++) f[i]=f[i-1]+f[i-2];
	int t; scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		
		ll res=0;
		n++;
		for(int i=B-1;i>=0;i--) if(n>>i&1){
			res+=f[i];
			if((n>>i&3)==3) break;
		}
		printf("%lld\n",res-1);
		n--;
		
		opt[O][0][0]=0;
		opt[O][1][0]=1;
		opt[O][0][1]=1;
		opt[O][1][1]=1;
		ans[A][0]=f[0];
		ans[A][1]=f[1];
		for(;n;n>>=1,mulopt())
			if(n&1) mulans();
		printf("%lld\n",ans[A][0]);
	}
}

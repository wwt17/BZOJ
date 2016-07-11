#include <cstdio>
typedef long long ll;
const int M=1000005,mo=100000007;
int n,m,f[M];
ll power(ll a,ll b){
	a%=mo;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	f[0]=1;
	f[1]=0;
	ll tot=power(2,n)-1,fac=1,per=1;
	for(int i=2;i<=m;i++){
		fac=fac*i%mo;
		per=per*(tot-(i-1)+1)%mo;
		f[i]=(per-f[i-1]-f[i-2]*ll(i-1)%mo*(tot-(i-2)))%mo;
	}
	printf("%d\n",int((f[m]*power(fac,mo-2)%mo+mo)%mo));
}

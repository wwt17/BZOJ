#include <cstdio>
typedef long long ll;

ll n;
int k,mo,gen;

ll power(ll a,int b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

void getgen(){
	if(mo==2){
		gen=1;
		return;
	}
	for(gen=2;gen<mo;gen++){
		bool ok=true;
		for(ll d=2;d*d<=mo-1;d++) if((mo-1)%d==0){
			if(power(gen,d)==1||power(gen,(mo-1)/d)==1){
				ok=false;
				break;
			}
		}
		if(ok) break;
	}
}

ll ans[2][2],opt[2][2],tmp[2][2];
void mult(ll a[2][2],ll b[2][2],ll c[2][2]){
	tmp[0][0]=(a[0][0]*b[0][0]+a[0][1]*b[1][0])%mo;
	tmp[0][1]=(a[0][0]*b[0][1]+a[0][1]*b[1][1])%mo;
	tmp[1][0]=(a[1][0]*b[0][0]+a[1][1]*b[1][0])%mo;
	tmp[1][1]=(a[1][0]*b[0][1]+a[1][1]*b[1][1])%mo;
	c[0][0]=tmp[0][0];
	c[0][1]=tmp[0][1];
	c[1][0]=tmp[1][0];
	c[1][1]=tmp[1][1];
}

int work(){
	scanf("%lld%d%d",&n,&k,&mo);
	getgen();
	ll W=power(gen,(mo-1)/k),w=1;
	ll res=0;
	for(int j=0;j<k;j++,w=w*W%mo){
		opt[0][0]=0;
		opt[0][1]=opt[1][0]=opt[1][1]=w;
		opt[0][0]++;
		opt[1][1]++;
		ans[0][0]=ans[1][1]=1;
		ans[0][1]=ans[1][0]=0;
		for(ll t=n;t;t>>=1){
			if(t&1)
				mult(ans,opt,ans);
			mult(opt,opt,opt);
		}
		res=(res+ans[0][0]+ans[1][0])%mo;
	}
	return res*power(k,mo-2)%mo;
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",work());
}

#include <cstdio>
typedef long long ll;
const int maxw=1005,maxD=105,mo=(int)1e9+7;

ll power(ll a,int b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

int D,w,p[maxw],a[maxw],inv[maxD],C[maxD][maxD],B[maxD],c[maxD];
int v1[maxw],w1[maxw],v2[maxw],w2[maxw];

int main(){
	scanf("%d%d",&D,&w);
	for(int i=1;i<=w;i++) scanf("%d%d",&p[i],&a[i]);
	inv[1]=1;
	for(int i=2;i<=D+2;i++)
		inv[i]=ll(mo-mo/i)*inv[mo%i]%mo;
	for(int i=0;i<=D+1;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=j?(C[i-1][j-1]+C[i-1][j])%mo:1;
	B[0]=1;
	for(int i=1;i<=D+1;i++){
		for(int j=0;j<i;j++)
			B[i]=(B[i]+mo-(ll)B[j]*C[i+1][j]%mo)%mo;
		B[i]=(ll)B[i]*inv[i+1]%mo;
	}
	for(int j=0;j<=D;j++)
		c[D+1-j]=(ll)B[j]*C[D+1][j]%mo*inv[D+1]%mo;
	if(D) c[D]=(c[D]+1)%mo;
	int ans=0;
	for(int i=1;i<=w;i++){
		v1[i]=1;
		w1[i]=power(p[i],a[i]);
		v2[i]=power(p[i],D);
		w2[i]=power(p[i],a[i]-1);
	}
	for(int j=0;j<=D+1;j++){
		ll now=c[j];
		for(int i=1;i<=w;i++){
			now=now*(v1[i]+mo-v2[i])%mo;
			v1[i]=(ll)v1[i]*w1[i]%mo;
			v2[i]=(ll)v2[i]*w2[i]%mo;
		}
		ans=(ans+now)%mo;
	}
	printf("%d\n",ans);
}

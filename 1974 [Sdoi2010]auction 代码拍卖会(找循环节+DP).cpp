#include <cstdio>
typedef long long ll;
const int mo=999911659,P=505;
ll n,c;
int p;
int len,cir,seq[P*2],g[9][P*2][P], // 放了几个，实际位置，模P 
F,f[2][P][9][P]; // 放了几个，循环中的位置，有几个相邻元素可以重叠，模P 
ll prod[50],iprod[50],ifac[50];
void inc(int &a,const int b){
	if((a+=b)>=mo) a-=mo;
}
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
ll power(ll a,ll b){
	a%=mo;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
void init(){
	prod[0]=1;
	iprod[0]=1;
	ifac[0]=1;
	for(int i=1;i<=20;i++){
		prod[i]=(c+8-i)%mo*prod[i-1]%mo;
		iprod[i]=iprod[i-1]*power(c+8-i,mo-2)%mo;
		ifac[i]=ifac[i-1]*power(i,mo-2)%mo;
	}
}
ll C(ll n,int m){
	return iprod[c+8-n-1]*prod[c+8-(n-m)-1]%mo*ifac[m]%mo;
}
int main(){
	scanf("%lld%d",&n,&p);
	seq[0]=1;
	for(int i=1;;i++){
		seq[i]=(seq[i-1]*10+1)%p;
		for(int j=0;j<i;j++) if(seq[i]==seq[j]){
			cir=i-j;
			len=j+(n-j+cir)%cir;
			c=(n-len)/cir;
			for(i++;i<len+cir;i++)
				seq[i]=(seq[i-1]*10+1)%p;
			goto out;
		}
	}
	out:;
	for(int i=0;i<=8;i++)
		g[i][0][0]=1;
	for(int i=0;i<=8;i++)
		for(int j=0;j<len;j++)
			for(int l=0;l<p;l++){
				inc(g[i][j+1][l],g[i][j][l]);
				if(i<8) inc(g[i+1][j][(l+seq[j])%p],g[i][j][l]);
			}
	if(n<=len){
		printf("%d\n",g[8][n][(p-seq[n-1])%p]);
		return 0;
	}
	int ans=0;
	init();
	for(int i=0;i<=8;i++){
		if(i){
			for(int j=1;j<cir;j++)
				for(int k=0;k<=8;k++)
					for(int l=0;l<p;l++)
						inc(f[F][j][k][l],f[F][j-1][k][l]);
			for(int j=0;j<cir;j++)
				for(int k=0;k<=8;k++)
					for(int r=gcd(p,seq[len+j])-1;r>=0;r--){
						int tmp=f[F][j][k][r],l;
						for(l=r;(l-seq[len+j]+p)%p!=r;l=(l-seq[len+j]+p)%p){
							f[F][j][k][l]=f[F][j][k][(l-seq[len+j]+p)%p];
						}
						f[F][j][k][l]=tmp;
					}
		}
		else
			f[F][0][0][0]=1;
		for(int j=0;j<cir;j++)
			for(int k=0;k<=8;k++)
				for(int l=0;l<p;l++) if(f[F][j][k][l]){
					ans=(ans+C(c+k-1,i)*f[F][j][k][l]%mo*g[8-i][len][(p*2-seq[len+cir-1]-l)%p])%mo;
					if(i<8){
						if(k<8) inc(f[!F][j][k+1][l],f[F][j][k][l]);
						inc(f[!F][0][k][l],f[F][j][k][l]);
						inc(f[!F][j][k][l],mo-f[F][j][k][l]);
					}
					f[F][j][k][l]=0;
				}
		F^=1;
	}
	printf("%d\n",(ans+mo)%mo);
}

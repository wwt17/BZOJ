#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mo=(7*17<<23)+1,gen=3,logN=18,N=1<<logN;
ll power(ll a,ll b){
	a%=mo;
	b=(b%(mo-1)+(mo-1))%(mo-1);
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
int bs,n,m,mrev[N*2],*rev[logN+1],w1[2][logN+1],c[N],f[N],g[N],a[N],b[N];
void fft(int *a,int bs,int f){
	for(int i=0;i<1<<bs;i++) if(i<rev[bs][i])
		swap(a[i],a[rev[bs][i]]);
	for(int lv=0,l=1;lv<bs;lv++,l<<=1)
		for(int i=0;i<1<<bs;i+=l<<1)
			for(int j=0,w=1;j<l;j++,w=1LL*w*w1[f][lv+1]%mo){
				int x=a[i+j],y=1LL*w*a[i+l+j]%mo;
				a[i+j]=(x+y)%mo,a[i+l+j]=(x-y+mo)%mo;
			}
	if(f){
		ll inv=power(1<<bs,-1);
		for(int i=0;i<1<<bs;i++) a[i]=a[i]*inv%mo;
	}
}
void work(int beg,int lv){
	if(lv==0){
		if(beg==0){
			f[beg]=1;
			g[beg]=1;
		}
		else{
			g[beg]=(g[beg]+2LL*f[beg])%mo;
		}
		return;
	}
	int mid=beg+(1<<lv-1);
	work(beg,lv-1);
	
	for(int i=0;i<1<<lv-1;i++) a[i]=g[beg+i];
	for(int i=1<<lv-1;i<1<<lv;i++) a[i]=0;
	fft(a,lv,0);
	for(int i=0;i<1<<lv;i++) b[i]=c[i];
	fft(b,lv,0);
	for(int i=0;i<1<<lv;i++) a[i]=1LL*a[i]*b[i]%mo;
	fft(a,lv,1);
	for(int i=1<<lv-1;i<1<<lv;i++) (f[beg+i]+=a[i])%=mo;
	
	for(int i=0;i<1<<lv-1;i++) a[i]=f[beg+i];
	for(int i=1<<lv-1;i<1<<lv;i++) a[i]=0;
	fft(a,lv,0);
	for(int i=0;i<1<<lv;i++) b[i]=i<beg?2*f[i]%mo:i<mid?f[i]:0;
	fft(b,lv,0);
	for(int i=0;i<1<<lv;i++) a[i]=1LL*a[i]*b[i]%mo;
	fft(a,lv,1);
	for(int i=1<<lv-1;i<1<<lv;i++) (g[beg+i]+=a[i])%=mo;
	
	work(mid,lv-1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(bs=0;(1<<bs)<m+1;bs++);
	for(int lv=0;lv<=bs;lv++){
		rev[lv]=mrev+(1<<lv);
		for(int i=0;i<1<<lv;i++)
			for(int j=0;j<lv;j++)
				rev[lv][i]=rev[lv][i]<<1|(i>>j&1);
	}
	for(int lv=1;lv<=bs;lv++){
		w1[0][lv]=power(gen,mo-1>>lv);
		w1[1][lv]=power(w1[0][lv],-1);
	}
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		c[x]=1;
	}
	work(0,bs);
	for(int i=1;i<=m;i++) printf("%d\n",f[i]);
	scanf("\n");
}

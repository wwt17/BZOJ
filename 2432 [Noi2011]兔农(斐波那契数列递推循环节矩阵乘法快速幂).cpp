#include <cstdio>
#include <cstring>
typedef long long ll;
const int K=int(1e6)+5,M=6*K,S=3;
const ll
// f[i] f[i+1] 1
opt1[S][S]={
	0,1,0,
	1,1,0,
	0,0,1
},
opt2[S][S]={
	0,1,0,
	1,1,0,
	0,-1,1
};
ll n;
int k,m,p,O,A;
ll ans[S][S],opt[S][S];
int len[K],inv[K],f[M],g[M];
bool vis[K];
void mini(int &a,const int b){
	if(b<a) a=b;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		if(a!=1) return 0;
		x=1;
		y=0;
		return a;
	}
	ll g=exgcd(b,a%b,y,x);
	if(!g) return 0;
	y-=a/b*x;
	// b*(x-a/b*y)+a*y=1
	return g;
}
inline void mul(ll c[S][S],const ll a[S][S],const ll b[S][S]){
	for(int i=0;i<S;i++)
		for(int j=0;j<S;j++){
			c[i][j]=0;
			for(int k=0;k<S;k++)
				(c[i][j]+=a[i][k]*b[k][j])%=p;
		}
}
inline void power(ll ans[S][S],const ll opt[S][S],ll q){
	static int O=0,A=0;
	static ll Ans[2][S][S],Opt[2][S][S];
	memcpy(Ans[A],ans,sizeof(opt1));
	memcpy(Opt[O],opt,sizeof(opt1));
	for(;q;q>>=1){
		if(q&1){
			mul(Ans[!A],Ans[A],Opt[O]);
			A^=1;
		}
		mul(Opt[!O],Opt[O],Opt[O]);
		O^=1;
	}
	memcpy(ans,Ans[A],sizeof(opt1));
}
int calc(){
	return ((g[m-1]*ans[0][1]%p+(g[m]+p-1)*ans[1][1]%p+ans[2][1])%p+p)%p;
}
int main(){
	scanf("%lld%d%d",&n,&k,&p);
	for(int i=1;i<k;i++){
		ll x=0,y;
		exgcd(i,k,x,y);
		inv[i]=(x%k+k)%k;
	}
	for(int i=0;i<k;i++) len[i]=1e9;
	f[0]=g[0]=0;
	f[1]=g[1]=1;
	f[2]=g[2]=1;
	for(int i=3;i<=6*k;i++){
		f[i]=(f[i-1]+f[i-2])%k;
		g[i]=(g[i-1]+g[i-2])%p;
		if(f[i]==1)
			if(!m) m=i;
		if(inv[f[i]])
			mini(len[inv[f[i]]],i);
	}
	if(n<m){
		printf("%d\n",g[n]);
		return 0;
	}
	n-=m;
	for(int i=0;i<S;i++) ans[i][i]=1;
	for(int v=f[m-1];;){
		if(vis[v]){
			for(int i=0;i<S;i++) opt[i][i]=1;
			ll cir=0;
			for(int u=v;;){
				if(!vis[u]) break;
				vis[u]=0;
				power(opt,opt1,len[u]-1);
				power(opt,opt2,1);
				cir+=len[u];
				u=1LL*u*f[len[u]-1]%k;
			}
			power(ans,opt,n/cir);
			n%=cir;
		}
		vis[v]=1;
		if(len[v]==1e9||n<len[v]){
			power(ans,opt1,n);
			printf("%d\n",calc());
			return 0;
		}
		power(ans,opt1,len[v]-1);
		power(ans,opt2,1);
		n-=len[v];
		v=1LL*v*f[len[v]-1]%k;
	}
}

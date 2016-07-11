#include <cstdio>
typedef long long ll;
const int N=1000005,M=N;
int n,m,L,R,D,f[N],w[M],h[M],last[N];
struct data{
	ll delta,max;
} t[N*4];
void add(int x,int beg,int end){
	if(R<=beg||L>=end) return;
	if(L<=beg&&R>=end){
		t[x].delta+=D;
		t[x].max+=D;
		return;
	}
	int mid=beg+end>>1;
	add(x<<1,beg,mid);
	add(x<<1|1,mid,end);
	t[x].max=(t[x<<1].max>t[x<<1|1].max?t[x<<1].max:t[x<<1|1].max)+t[x].delta;
}
ll ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",f+i);
	for(int i=1;i<=m;i++) scanf("%d",w+i);
	for(int i=1;i<=n;i++){
		last[i]=h[f[i]];
		h[f[i]]=i;
		L=last[i],R=i,D=w[f[i]];
		add(1,0,n);
		L=last[last[i]],R=last[i],D*=-1;
		if(L<R) add(1,0,n);
		if(t[1].max>ans) ans=t[1].max;
	}
	printf("%lld\n",ans);
}

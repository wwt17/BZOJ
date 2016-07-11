#include <cstdio>
typedef long long ll;
const int Len=(int)5e4+5;

int len;
int mu[Len];
ll t[Len];

void inc(int x,int d){
	if(!d) return;
	for(;x<=len;x+=x&-x) t[x]+=d;
}
ll query(int x){
	ll ans=0;
	for(;x;x-=x&-x) ans+=t[x];
	return ans;
}

int main(){
	mu[1]=1;
	for(int i=1;i<Len;i++)
		for(int j=i*2;j<Len;j+=i)
			mu[j]-=mu[i];
	int m;
	for(int Case=1;scanf("%d%d",&len,&m),len;Case++){
		printf("Case #%d:\n",Case);
		for(int i=1;i<=len;i++) t[i]=0;
		while(m--){
			int type; scanf("%d",&type);
			if(type==1){
				int n,d,v; scanf("%d%d%d",&n,&d,&v);
				if(n%d) continue;
				n/=d;
				for(int i=1;i*i<=n;i++) if(n%i==0){
					if(i*d<=len) inc(i*d,mu[i]*v);
					if(i*i==n) continue;
					i=n/i;
					if(i*d<=len) inc(i*d,mu[i]*v);
					i=n/i;
				}
			}
			else{
				int n; scanf("%d",&n);
				ll ans=0,las=0,now;
				for(int l=0,r;l<n;l=r,las=now){
					r=n/(n/(l+1));
					now=query(r);
					ans=ans+n/r*(now-las);
				}
				printf("%lld\n",ans);
			}
		}
	}
}

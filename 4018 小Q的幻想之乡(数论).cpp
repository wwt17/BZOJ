#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=(int)2e6+5,mo1=(int)1e9+7,mo2=(int)1e9+9,maxT=1005;

int mo;

int q[maxT][2];

int prime[N],p[N];
ll pre[N];

void init(int n){
	pre[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		if(p[i]==p[i/p[i]]){
			pre[i]=pre[i/p[i]];
		}
		else{
			pre[i]=pre[i/p[i]]*(1-p[i]);
		}
		for(int j=1;j<=*prime&&i*prime[j]<=n&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
	for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
}

inline ll sum(long long B,long long A){
	if(!A||!B) return 0;
	if(A>B) swap(A,B);
	return ((A-1)*A*(A+1)/3%mo+A*B*(B-A)/2%mo)%mo;
}

int Main(int n,int m){
	ll ans=0;
	for(int l=0,r;l<n&&l<m;l=r){
		int x=n/(l+1),y=m/(l+1);
		r=min(n/x,m/y);
		ans=(ans+(pre[r]-pre[l])*sum(x,y))%mo;
	}
	ans=(ans+mo)%mo;
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	int n=0;
	for(int Case=0;Case<T;Case++){
		scanf("%d%d",&q[Case][0],&q[Case][1]);
		if(q[Case][0]>q[Case][1]) swap(q[Case][0],q[Case][1]);
		n=max(n,q[Case][1]);
	}
	init(n);
	for(int Case=0;Case<T;Case++){
		int n=q[Case][0],m=q[Case][1];
		mo=mo1;
		printf("%d ",Main(n,m));
		mo=mo2;
		printf("%d\n",Main(n,m));
	}
}

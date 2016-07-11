#include <cstdio>
#include <algorithm>
using namespace std;
const int K=1000005,P=19940417;
long long n,h; int k;
typedef pair<long long,long long> data;
data q[K];
int f[K],g[K];
inline long long power(long long b){
	long long a=2,ret=1;
	for(;b;b>>=1,a=a*a%P) if(b&1) ret=(ret*a)%P;
	return ret;
}
int main(){
	scanf("%lld%d",&n,&k); k++;
	q[0]=data(0,0);
	for(int i=1;i<k;i++) scanf("%lld%lld",&q[i].first,&q[i].second);
	q[k]=data(n,0);
	sort(q,q+k);
	g[0]=1;
	for(int i=0;i<k;i++){
		if(q[i]==q[i+1]){
			g[i+1]=g[i];
			f[i+1]=f[i];
			continue;
		}
		long long d=q[i+1].first-q[i].first-q[i].second-q[i+1].second;
		if(q[i].second)
			if(q[i+1].second)
				if(d>=0){
					d>>=1;
					long long tmp=d>0?power(d-1):1;
					g[i+1]+=f[i]*tmp%P;
					g[i+1]+=g[i]*(d>1?tmp:d==1?1:0)%P;
					f[i+1]+=f[i]*(d>1?tmp:d==1?1:0)%P;
					f[i+1]+=g[i]*((d>1?tmp-1:0)+1)%P;
				}
				else
					if(q[i+1].second>q[i].second)
						if(q[i+1].second-q[i].second==q[i+1].first-q[i].first)
							g[i+1]=g[i];
						else
							f[i+1]=g[i];
					else
						if(q[i+1].second-q[i].second==q[i].first-q[i+1].first)
							f[i+1]=f[i];
						else
							f[i+1]=g[i];
			else{
				d>>=1;
				long long tmp=d>0?power(d-1):1;
				g[i+1]+=f[i]*tmp%P;
				g[i+1]+=g[i]*(d>1?tmp:d==1?1:0)%P;
				f[i+1]=0;
			}
		else
			if(q[i+1].second){
				d>>=1;
				long long tmp=d>0?power(d-1):1;
				g[i+1]=g[i]*tmp%P;
				f[i+1]=g[i]*(d>1?tmp:d==1?1:0)%P;
			}
			else{
				d>>=1;
				long long tmp=d>0?power(d-1):1;
				g[i+1]=g[i]*tmp%P;
			}
		f[i+1]+=g[i+1];
		if(g[i]) h=max(h,(q[i+1].first-q[i].first+q[i].second+q[i+1].second)>>1);
	}
	printf("%d %lld\n",f[k]%P,h);
}

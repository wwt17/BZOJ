//sigma(D) (n/D)*(m/D)* sigma(d|D) f(d)*miu(D/d)
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1e5+5,Q=2e4+5;
inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int q,n,primes,prime[N],p[N],pp[N],miu[N],f[N],ord[N],t[N];
bool cmp(const int a,const int b){
	return f[a]<f[b];
}
void add(int d){
	for(int dd=1;d*dd<=n;dd++){
		int v=f[d]*miu[dd];
		for(int x=d*dd;x<=n;x+=x&-x) t[x]+=v;
	}
}
int ans[Q];
struct query{
	int num,n,m,a;
	void read(){
		scanf("%d%d%d",&n,&m,&a);
		if(n>::n) ::n=n;
		if(m>::n) ::n=m;
	}
	bool operator < (const query &b) const{
		return a<b.a;
	}
	void calc(){
		int res=0,last=0;
		for(int i=0;i<n&&i<m;){
			int j=min(n/(n/(i+1)),m/(m/(i+1))),cur=0;
			for(int x=j;x;x-=x&-x) cur+=t[x];
			res+=(n/j)*(m/j)*(cur-last);
			last=cur;
			i=j;
		}
		ans[num]=res;
	}
} seq[Q];
int main(){
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		seq[i].num=i;
		seq[i].read();
	}
	f[1]=1;
	miu[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]){
			pp[i]=p[i]=prime[primes++]=i;
		}
		miu[i]=p[i]==p[i/p[i]]?0:-miu[i/p[i]];
		f[i]=f[i/p[i]]+f[i/pp[i]]*pp[i];
		for(int j=0;j<primes&&prime[j]<=p[i]&&i*prime[j]<N;j++){
			p[i*prime[j]]=prime[j];
			if(prime[j]==p[i]){
				pp[i*prime[j]]=pp[i]*p[i];
			}
			else{
				pp[i*prime[j]]=prime[j];
			}
		}
	}
	for(int i=1;i<=n;i++) ord[i]=i;
	sort(ord+1,ord+n+1,cmp);
	sort(seq,seq+q);
	for(int i=0,j=1;i<q;i++){
		for(;j<=n&&f[ord[j]]<=seq[i].a;j++)
			add(ord[j]);
		seq[i].calc();
	}
	for(int i=0;i<q;i++) printf("%d\n",ans[i]&0x7fffffff);
	scanf("\n");
}

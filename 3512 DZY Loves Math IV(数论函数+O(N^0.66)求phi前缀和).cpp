#include <cstdio>
typedef long long ll;

const int N=(int)1e6+5,mo=(int)1e9+7,P=10000007;

int n,m;

int prime[N],p[N],pp[N],phi[N],sphi[N];

void init(int n){
	pp[1]=1;
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		if(p[i]==p[i/p[i]]){
			pp[i]=pp[i/p[i]];
			phi[i]=phi[i/p[i]]*p[i];
		}
		else{
			pp[i]=pp[i/p[i]]*p[i];
			phi[i]=phi[i/p[i]]*(p[i]-1);
		}
		for(int j=1;j<=*prime&&i*prime[j]<=n&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
	for(int i=1;i<=n;i++) sphi[i]=(sphi[i-1]+phi[i])%mo;
}

struct data{
	int n,m,val;
	data *next;
} mem[3000005],*topmem=mem;

int hash(int n,int m){
	return (1LL*m*N+n)%P;
}

data *head[P];

int Sum(int n,int m){
	if(m==0) return 0;
	if(pp[n]!=n) return ll(n/pp[n])*Sum(pp[n],m)%mo;
	if(n==1&&m<N) return sphi[m];
	int h=hash(n,m);
	for(data *p=head[h];p;p=p->next) if(p->n==n&&p->m==m)
		return p->val;
	int ans=0;
	if(n==1){
		ans=m*(m+1LL)/2%mo;
		for(int l=0,las=0,r,now;m/(l+1)>1;l=r,las=now){
			r=m/(m/(l+1));
			now=Sum(1,r);
			ans=(ans-(now-las)*(m/r-1LL))%mo;
		}
	}
	else{
		for(int d=1;d*d<=n;d++) if(n%d==0){
			ans=(ans+1LL*phi[n/d]*Sum(d,m/d))%mo;
			if(d*d!=n)
				ans=(ans+1LL*phi[d]*Sum(n/d,m/(n/d)))%mo;
		}
	}
	*topmem=(data){n,m,ans,head[h]}; head[h]=topmem++;
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	init(N-1);
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+Sum(i,m))%mo;
	printf("%d\n",(ans+mo)%mo);
}

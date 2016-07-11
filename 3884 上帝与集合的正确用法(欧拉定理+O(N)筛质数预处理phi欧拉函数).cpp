#include <cstdio>
const int N=(int)1e7+5,T=1005;
int n,q[T],prime[N/2],p[N],phi[N];

void init(){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		if(p[i/p[i]]==p[i]) phi[i]=phi[i/p[i]]*p[i]; else phi[i]=phi[i/p[i]]*(p[i]-1);
		for(int j=1;j<=*prime&&i*prime[j]<=n&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
}

long long power(long long a,long long b,int p){
	b%=phi[p];
	if(b<0) b+=phi[p];
	long long ans=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}

int f(int p){
	if(p==1) return 0;
	int q=p;
	int cnt=0;
	while(!(q&1)){
		q>>=1;
		cnt++;
	}
	return (power(2,f(phi[q])-cnt,q)<<cnt)%p;
}

int main(){
	int t; scanf("%d",&t);
	for(int i=0;i<t;i++){
		scanf("%d",&q[i]);
		if(q[i]>n) n=q[i];
	}
	init();
	for(int i=0;i<t;i++)
		printf("%d\n",f(q[i]));
}

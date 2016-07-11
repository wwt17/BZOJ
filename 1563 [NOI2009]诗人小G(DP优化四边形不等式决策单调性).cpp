#include <cstdio>
#include <cstring>
typedef long long ll;
const int N=100005;
const ll inf=(ll)1e18+1;
int n,L,P,s[N];
ll f[N];
char sent[35];
int top;
struct interval{
	int s,deci;
} q[N];
double fpowp(double a){
	if(a<0) a*=-1;
	double ans=1;
	for(int b=P;b;a=a*a,b>>=1)
		if(b&1) ans*=a;
	return ans;
}
ll powp(ll a){
	if(a<0) a*=-1;
	ll ans=1;
	for(int b=P;b;a=a*a,b>>=1)
		if(b&1) ans*=a;
	return ans;
}
double fcalc(int i,int j){
	double ans=f[j]+fpowp(s[i]-s[j]-L);
	return ans;
}
ll calc(int i,int j){
	return f[j]+powp(s[i]-s[j]-L);
}
void work(){
	scanf("%d%d%d",&n,&L,&P);
	L++;
	for(int i=1;i<=n;i++){
		scanf("%s",sent);
		s[i]=s[i-1]+strlen(sent)+1;
	}
	top=1;
	q[top].s=0;
	q[top].deci=0;
	for(int i=1,last=1;i<=n;i++){
		while(last<top&&q[last+1].s<i) last++;
		f[i]=calc(i,q[last].deci);
		if(fcalc(i,q[last].deci)>=1.5*inf||f[i]>=inf){
			f[i]=inf;
			continue;
		}
		while(top>last&&fcalc(q[top].s+1,i)<=fcalc(q[top].s+1,q[top].deci)) top--;
		int l=q[top].s+1,r=n+1;
		while(r-l>1){
			int mid=l+r>>1;
			if(fcalc(mid,i)<=fcalc(mid,q[top].deci))
				r=mid;
			else
				l=mid;
		}
		if(l>=n) continue;
		++top;
		q[top].s=l;
		q[top].deci=i;
	}
	if(f[n]<inf)
		printf("%lld\n",f[n]);
	else
		puts("Too hard to arrange");
	puts("--------------------");
}
int main(){
	int T; scanf("%d",&T);
	while(T--)
		work();
}

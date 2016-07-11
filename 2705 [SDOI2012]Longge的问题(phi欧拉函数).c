long long n,t,ans=0;
int cnt=0,p[32],c[32];
void solve(int i,long long k,long long phindk){
	if(i==cnt){
		ans+=k*phindk;
		return;
	}
	solve(i+1,k,phindk);
	solve(i+1,k/=p[i],phindk*=p[i]-1);
	for(int j=2;j<=c[i];j++)
		solve(i+1,k/=p[i],phindk*=p[i]);
}
int main(){
	scanf("%lld",&n);
	t=n;
	for(int i=2;(long long)i*i<=t;i++) if(!(t%i)){
		p[cnt]=i;
		do{ c[cnt]++; t/=i; } while(!(t%i));
		cnt++;
		if(t==1) break;
	}
	if(t>1) p[cnt]=t,c[cnt]=1,cnt++;
	solve(0,n,1);
	printf("%lld\n",ans);
}

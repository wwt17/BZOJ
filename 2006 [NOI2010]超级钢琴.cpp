#include <cstdio>
#include <queue>
#define N 500001
#define logN 19
#define ll long long
int n,lg[N],i,ii,j,k,L,R;
struct data{
	ll min; int loc;
} ST[logN][N];
inline data& min(data &a,data &b){
	return a.min<b.min?a:b;
}
inline data& query(const int l,const int r){
	static int j; j=lg[r-l+1]-1;
	return min(ST[j][l],ST[j][r-(1<<j)+1]);
}
struct interval{
	int i,l,r; ll max; data f;
	friend bool operator < (const interval &a,const interval &b){
		return a.max < b.max;
	}
	inline void correct(){
		max=(*ST)[i].min-(f=query(l,r)).min;
	}
} r[N];
ll Ans=0;
int main(){
	scanf("%u%u%d%d",&n,&k,&L,&R);
	for(i=1;i<=n;++i)
		lg[i]=lg[i>>1]+1,
		scanf("%lld",&(*ST)[i].min),
		(*ST)[i].min+=(*ST)[i-1].min,
		(*ST)[i].loc=i;
	for(j=1;j<lg[n];++j)
		for(i=0,ii=1<<(j-1);i<=n-(1<<j);++i,++ii)
			ST[j][i]=min(ST[j-1][i],ST[j-1][ii]);
	for(i=L;i<=n;++i)
		r[i].i=i,
		r[i].l=std::max(0,i-R),
		r[i].r=i-L,
		r[i].correct();
	std::priority_queue<interval> q(r+L,r+n+1);
	while(k--){
		static interval s,t;
		s=q.top(); q.pop();
		Ans+=s.max;
		t.i=s.i;
		if((t.l=s.l)<=(t.r=s.f.loc-1))
			t.correct(), q.push(t);
		if((t.l=s.f.loc+1)<=(t.r=s.r))
			t.correct(), q.push(t);
	}
	printf("%lld\n",Ans);
}

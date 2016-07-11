#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
template<class T,class T2,int P,int hash(T)>
struct s_hash_map{
	typedef std::pair<T,T2> value_type;
	typedef value_type* iterator;
	value_type* a[P];
	int q[P],*top;
	s_hash_map():top(q){
	}
	~s_hash_map(){
		clear();
	}
	value_type* end(){
		return NULL;
	}
	int findloc(const T& x){
		int loc=hash(x);
		while(a[loc]){
			if(a[loc]->first==x)
				return loc;
			if(++loc==P) loc=0;
		}
		return loc;
	}
	bool empty(){
		return top==q;
	}
	int size(){
		return top-q;
	}
	std::pair<iterator,bool> insert(const value_type& x){
		int loc=findloc(x.first);
		if(a[loc]) return std::make_pair(a[loc],false);
		if(top-q==P-1) return std::make_pair((value_type*)NULL,false);
		*top++=loc;
		return std::make_pair(a[loc]=new value_type(x),true);
	}
	void clear(){
		while(top>q){
			int loc=*--top;
			delete a[loc];
			a[loc]=NULL;
		}
	}
	iterator find(const T& x){
		return a[findloc(x)];
	}
	int count(const T& x){
		return a[findloc(x)]?1:0;
	}
	T2& operator [] (const T& x){
		int loc=findloc(x);
		if(!a[loc])
			a[*top++=loc]=new value_type(x,T2());
		return a[loc]->second;
	}
	s_hash_map& operator = (s_hash_map& b){
		if(&b==this) return *this;
		clear();
		for(int *i=b.q;i<b.top;i++){
			int loc=*i;
			a[loc]=b.a[loc];
			*top++=loc;
		}
		return *this;
	}
};

inline ll power(ll a,ll b,ll p){
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}
ll ex_gcd_x,ex_gcd_y;
ll ex_gcd(ll a,ll b){
	if(!b){
		ex_gcd_x=1;
		ex_gcd_y=0;
		return a;
	}
	ll g=ex_gcd(b,a%b);
	if(g==-1) return g;
	ll t=ex_gcd_x;
	ex_gcd_x=ex_gcd_y;
	ex_gcd_y=t-a/b*ex_gcd_y;
	return g;
}
ll ex_gcd(ll a,ll b,ll &x,ll &y=ex_gcd_y){
	// ax+by=gcd(a,b)
	ll g=ex_gcd(a,b);
	x=ex_gcd_x;
	y=ex_gcd_y;
	x=(x%b+b)%b;
	return g;
}

ll inv(ll x,ll p){
	ll t;
	ex_gcd(x,p,t);
	return t;
}

const int hsize=10000007;

int hash(ll x){
	return x%hsize;
}

typedef s_hash_map<ll,int,hsize,hash> sli;

sli s;

inline ll BSGS(ll a,ll c,ll p){
	a%=p;
	c%=p;
	s.clear();
	ll t=inv(a,p);
	ll m=sqrt(p-1);
	for(ll i=0;i<m;i++,c=c*t%p){
		int &tmp=s[c];
		if(!tmp) tmp=i+1;
	}
	ll aa=power(a,m,p),aaa=1;
	for(ll i=0;i<p-1;i+=m,aaa=aaa*aa%p){
		sli::iterator tmp=s.find(aaa);
		if(tmp!=s.end())
			return i+tmp->second-1;
	}
	return -1;
}

inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}

ll x0,a,b,c,p;

int main(){
	int T; scanf("%d",&T);
	while(T--){
		p=getint(),a=getint(),b=getint(),x0=getint(),c=getint();
		if(a==0){
			puts(x0==c?"1":b==c?"2":"-1");
			continue;
		}
		if(a==1){
			if(!b){
				printf("%d\n",x0==c?1:-1);
				continue;
			}
			printf("%d\n",int((c-x0+p)%p*inv(b,p)%p)+1);
			continue;
		}
		ll A=(x0*(a-1)+b)%p,C=(c*(a-1)+b)%p;
		if(!A){
			printf("%d\n",C==0?1:-1);
			continue;
		}
		int ans=BSGS(a,C*inv(A,p)%p,p);
		if(ans==-1){
			puts("-1");
			continue;
		}
		printf("%d\n",int(ans)+1);
	}
}

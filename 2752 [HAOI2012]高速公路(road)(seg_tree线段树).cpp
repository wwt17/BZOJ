#include <cstdio>
#include <cstdlib>
#define ll long long
inline void read(int &a){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0'; if(f) a=-a;
}
inline void write(unsigned ll a){
	if(a>9) write(a/10); putchar('0'+a%10);
}
inline void write(ll a){
	if(a<0){ putchar('-');a=-a; }
	if(a>9) write((unsigned ll)a/10); putchar('0'+a%10);
}
template<class T>
T gcd(const T a,const T b){
	return b?gcd(b,a%b):a;
}

int N,M,Base,maxlg,l,r,v; ll costw[131072],Add[262144];
struct data{
	ll cost,s,sl,sr; int len;
	inline void add(const int x){
		cost+=costw[len]*x;
		s+=(ll)len*x;
		static ll tmp; tmp=((ll)(len+1)*len>>1)*x;
		sl+=tmp;
		sr+=tmp;
	}
	friend data operator+(const data &a,const data &b){
		return (data){
			a.cost+b.cost+a.sr*b.len+b.sl*a.len,
			a.s+b.s,
			a.sl+b.sl+a.s*b.len,
			b.sr+a.sr+b.s*a.len,
			a.len+b.len,
			};
	}
} null,t[262144];
#define down(i) if(Add[i])\
	Add[i<<1]+=Add[i],t[i<<1].add(Add[i]),\
	Add[i<<1|1]+=Add[i],t[i<<1|1].add(Add[i]),\
	Add[i]=0
#define update(i) t[i]=t[i<<1]+t[i<<1|1]
void correct(int i){
	if(i>>=1){ correct(i); down(i); }
}
int main(){
	read(N),read(M);
	for(costw[Base=1]=1;Base<N;Base<<=1)
		costw[Base<<1]=(costw[Base]<<1)+(ll)(Base+1)*Base*Base;
	l=Base,r=Base+N;
	for(int i=l+1;i<r;i++) t[i].len=1;
	for(l>>=1,r>>=1;l^r^1;l>>=1,r>>=1)
		for(int i=l+1;i<r;i++) t[i].len=t[i<<1].len+t[i<<1|1].len;
	char ch;
	while(M--){
		while((ch=getchar())!='C'&&ch!='Q');
		if(ch=='C'){
			read(l),read(r),read(v);
			for(correct(l+=Base-1),correct(r+=Base);l^r^1;l>>=1,update(l),r>>=1,update(r)){
				if(!(l&1)) Add[l^1]+=v,t[l^1].add(v);
				if(  r&1 ) Add[r^1]+=v,t[r^1].add(v);
			}
			while(l>>=1) update(l);
		}
		else{
			read(l),read(r);
			data suml=null,sumr=null;
			for(correct(l+=Base-1),correct(r+=Base);l^r^1;l>>=1,r>>=1){
				if(!(l&1)) suml=suml+t[l^1];
				if(  r&1 ) sumr=t[r^1]+sumr;
			}
			suml=suml+sumr;
			ll tmp=(ll)(suml.len+1)*suml.len>>1,g=gcd(suml.cost,tmp);
			write(suml.cost/g),putchar('/'),write(tmp/g),putchar('\n');
		}
	}
}

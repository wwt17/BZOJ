#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define size 100001
inline void read(int &a){
	char c;bool f;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	a=(f=(c=='-'))?0:c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+c-'0';
	if (f) a=-a;
}
int N,i; long long ans[size],Ans=0x7FFFFFFFFFFFFFFFLL;
struct state{
	int x; long long* p;
	friend bool operator < (const state &a,const state &b){
		return a.x<b.x;
	}
} x[size],y[size];
void calc(state x[]){
	std::sort(x+1,x+N+1); x[0].x=x[1].x;
	long long suml=0,sumr=0;
	for(i=1;i<=N;++i) sumr+=x[i].x; sumr-=(long long)N*x[1].x;
	long long k;
	for(int i=1;i<=N;++i){
		k=x[i].x-x[i-1].x;
		suml+=k*(i-1);
		sumr-=k*(N-i+1);
		*(x[i].p)+=suml+sumr;
	}
}
int main(){
	read(N);
	int X,Y;
	for(i=1;i<=N;++i){
		read(X),read(Y);
		x[i].x=X+Y;y[i].x=X-Y;
		x[i].p=y[i].p=ans+i;
	}
	calc(x);
	calc(y);
	for(i=1;i<=N;++i) if(Ans>ans[i]) Ans=ans[i];
	printf("%lld\n",Ans>>1);
}

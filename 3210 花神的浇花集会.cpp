//http://tieba.com/p/2301153699?pid=32169110255&cid=32432913399#32432913399
//xx=x+y,yy=x-y
//x=(xx+yy)/2,y=(xx-yy)/2
#include <cstdio>
#include <algorithm>
#define SIZE 100002
inline void read(int &a){
	char c; while(c=getchar(),c<'0'||'9'<c); a=c-'0';
	while(c=getchar(),'0'<=c&&c<='9') a=a*10+c-'0';
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read(a),read(b),read(c))
#define ll long long
int N,i,x[SIZE],y[SIZE],X,Y;
ll sx[SIZE],sy[SIZE];
#define work(x) \
	std::sort(x+1,x+N+1);\
	for(i=1;i<=N;++i) s##x[i]=s##x[i-1]+x[i];
#define calc(x,mid,k) (s##x[N]-s##x[mid]-(N-(mid))*(k)+(mid)*(k)-s##x[mid])
#define min(a,b,c,d) std::min(std::min(a,b),std::min(c,d))
inline int last(int *x){
	int mid=N>>1,X=x[mid]; for(x[0]=0x80000000;X==x[mid];--mid); return mid;
}
inline int next(int *x){
	int mid=N>>1,X=x[mid]; for(x[N+1]=0x7FFFFFFF;X==x[mid];++mid); return --mid;
}
int main(){
	read(N);
	for(i=1;i<=N;++i){
		read2(x[i],y[i]);
		x[i]+=y[i];
		y[i]=x[i]-y[i]*2;
	}
	work(x);
	work(y);
	int mid;
	printf("%llu\n",((x[N>>1]^y[N>>1])&1
		?min(
			(mid=last(y),calc(x,N>>1,x[N>>1])+calc(y,mid,y[N>>1]-1)),
			(mid=next(y),calc(x,N>>1,x[N>>1])+calc(y,mid,y[N>>1]+1)),
			(mid=last(x),calc(x,mid,x[N>>1]-1)+calc(y,N>>1,y[N>>1])),
			(mid=next(x),calc(x,mid,x[N>>1]+1)+calc(y,N>>1,y[N>>1])))
		:calc(x,N>>1,x[N>>1])+calc(y,N>>1,y[N>>1])
		)>>1);
}

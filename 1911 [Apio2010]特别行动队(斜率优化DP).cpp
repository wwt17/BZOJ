#include <cstdio>
#define long long long
#define N 1000001
inline long sqr(int x){return (long)x*x;}
int n,i,xi; long a,b,c;
struct data{
	long f; int s;
	inline long K()const{ return -2*a*s; }
	inline long B()const{ return f+a*sqr(s)-b*s; }
} q[N],current,*head=q,*tail=q;
inline double calc(data* data1,data* data2){
	return (double)(data2->B()-data1->B())/(data1->K()-data2->K());
}
int main(){
	scanf("%u%lld%lld%lld",&n,&a,&b,&c);
	for(i=1;i<=n;i++){
		#define X current.s
		scanf("%u",&xi); current.s+=xi;
		while(head<tail&&X>calc(head,head+1))
			head++;
		current.f=head->f+a*sqr(current.s-head->s)+b*(current.s-head->s)+c;
		while(head<tail&&calc(tail-1,tail)>=calc(tail,&current))
			tail--;
		*++tail=current;
	}
	printf("%lld\n",current.f);
}

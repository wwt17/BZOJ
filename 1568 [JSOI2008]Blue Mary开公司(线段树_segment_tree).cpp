#include <cstdio>
#include <algorithm>
using namespace std;
int m,n,d;
struct pro{
	double p,s;
	inline double calc(const double d){
		return s+p*d;
	}
} z,a,t[500005];
void add(int i,int l,int r,pro a){
	#define addl(A) add(i<<1,l,(l+r)>>1,A)
	#define addr(A) add(i<<1|1,(l+r)>>1,r,A)
	if(t[i].calc(l)<a.calc(l)&&t[i].calc(r-1)<a.calc(r-1))
		{ t[i]=a; return; }
	if(t[i].calc(l)>=a.calc(r)&&t[i].calc(r-1)>=a.calc(r-1))
		return;
	double k=a.p-t[i].p,b=a.s-t[i].s;
	double x=-(double)b/k;
	if(k>0)
		if(x<(l+r)>>1) addl(t[i]),t[i]=a;
		else addr(a);
	else
		if(x>(l+r)>>1) addr(t[i]),t[i]=a;
		else addl(a);
}
double query(int i,int l,int r){
	double ans=0;
	for(;;){
		if(ans<t[i].calc(d)) ans=t[i].calc(d);
		if(r-l==1) return ans;
		if(d<(l+r)>>1) r=(l+r)>>1,i<<=1;
		else l=(l+r)>>1,i=i<<1|1;
	}
}
int main(){
	scanf("%d",&m);
	while(m--)
		switch(getchar()){
			case 'Q': scanf("uery %d",&d); d--;
				printf("%d\n",(int)(query(1,0,50000)/100+1e-9));
				break;
			case 'P': scanf("roject %lf%lf",&a.s,&a.p);
				add(1,0,50000,a);
				break;
			default: m++;
		}
}

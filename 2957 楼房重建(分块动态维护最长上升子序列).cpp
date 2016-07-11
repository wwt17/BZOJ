#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
const int N=150005;
#define ran() (rand()<<16|rand())
inline int rang(int begin,int end){
	return begin+ran()%(end-begin);
}
int n,m,cnt,size,sum[N];
double a[N],b[N],*top[N],pmax[N];
int main(){
	scanf("%d%d",&n,&m); n++;
	#define calcO(S) ((S)+n/(S)*(log2(S)+1))
	int R=std::max(1,n/30);
	for(size=rand()%n,cnt=100;cnt;cnt--){
		int size_=rang(std::max(1,size-R),std::min(n,size+R));
		if(calcO(size)>=calcO(size_)) size=size_;
	}
	cnt=n/size+(bool)(n%size);
	for(int i=0;i<cnt;i++) top[i]=b+i*size;
	while(m--){
		static int x,y,i,j; scanf("%d%d",&x,&y);
		a[x]=(double)y/x;
		i=x/size;
		top[i]=b+i*size;
		double max=0;
		for(j=0;j<size;j++) if(a[i*size+j]>max)
			*top[i]++=max=a[i*size+j];
		max=i?pmax[i-1]:0;
		for(;i<cnt;i++){
			double *loc=std::upper_bound(b+i*size,top[i],max);
			sum[i]=(i?sum[i-1]:0)+(top[i]-loc);
			max=pmax[i]=top[i]-loc?top[i][-1]:max;
		}
		printf("%d\n",sum[cnt-1]);
	}
}

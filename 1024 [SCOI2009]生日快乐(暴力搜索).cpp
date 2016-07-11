#include <cstdio>
#include <algorithm>
using std::max;
#define float double
inline void tension(float &a,const float b){
	if(a>b) a=b;
}
float f(const float x,const float y,const int n){
	if(n==1) return x>y?x/y:y/x;
	float ans=100000000.0; int i;
	for(i=1;i<n;++i)
		tension(ans,max(f(x*i/n,y,i),f(x*(n-i)/n,y,n-i))),
		tension(ans,max(f(x,y*i/n,i),f(x,y*(n-i)/n,n-i)));
	return ans;
}
int main(){
	int X,Y,N; scanf("%u%u%u",&X,&Y,&N);
	printf("%f\n",f(X,Y,N));
}

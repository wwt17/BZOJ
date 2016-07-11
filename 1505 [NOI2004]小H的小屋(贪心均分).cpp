#include <cstdio>
const double inf=1./0;
double k1,k2,ans=inf;
int m,n;
void mini(double &a,const double b){
	if(b<a) a=b;
}
double calc3(int len){
	return len*len*k2;
}
double calc2(int len,int ech){
	return len*len*k1+len%ech*calc3(len/ech+1)+(ech-len%ech)*calc3(len/ech);
}
double calc(int len,int cnt,int ech){
	if(len==0) return cnt?inf:0;
	if(cnt==0) return inf;
	return len%cnt*calc2(len/cnt+1,ech)+(cnt-len%cnt)*calc2(len/cnt,ech);
}
int main(){
	scanf("%lf%lf%d%d",&k1,&k2,&m,&n);
	for(int x=n%m;x<=100-(m-n%m);x++)
		mini(ans,calc(x,n%m,n/m+1)+calc(100-x,m-n%m,n/m));
	printf("%.1lf\n",ans);
}

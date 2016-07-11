/*
X[i]=f[i]*Rate[i]/(Rate[i]*A[i]+1*B[i])
Y[i]=f[i]*1/(Rate[i]*A[i]+1*B[i])
f[i]=max(f[i-1],max{
	 X[j]*A[i]
	+Y[j]*B[i]
}) j<i
slope[i]=-A[i]/B[i]
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N=100005,logN=18;
const double eps=1e-7;
int n;
double f[N],A[N],B[N],Rate[N];
struct vec{
	double x,y,a;
} p[N];
int top[N],ord[N*logN],*newo=ord;

bool cmpxy(vec &A,vec &B){
	return A.a<B.a;
}
bool cmpAB(const int i,const int j){
	return A[i]*B[j]>A[j]*B[i];
}

bool close(vec &A,vec &B){
	return fabs(A.x-B.x)<eps&&fabs(A.y-B.y)<eps;
}
double cross(vec &A,vec &B,vec &C){
	return (B.x-A.x)*(C.y-A.y)-(C.x-A.x)*(B.y-A.y);
}

int *geto(int beg,int end,int *mem){
	if(end-beg==1){
		*mem=beg;
		return mem+1;
	}
	int mid=beg+end>>1;
	int *a=mem+end-beg;
	int *b=geto(beg,mid,a);
	int *c=geto(mid,end,b);
	merge(a,a+(mid-beg),b,b+(end-mid),mem,cmpAB);
	return c;
}

void solve(int beg,int end){ // CDQ
	newo+=end-beg;
	if(end-beg==1){
		#define i beg
		if(i) f[i]=max(f[i-1],f[i]);
		p[i].y=f[i]/(Rate[i]*A[i]+1*B[i]);
		p[i].x=p[i].y*Rate[i];
		p[i].a=atan2(1,Rate[i]);
		top[i]=i+1;
		return;
		#undef i
	}
	
	int mid=beg+end>>1;
	solve(beg,mid);
	int *o=newo;
	for(int i=beg,j=mid;j<end;j++){
		int k=o[j-mid];
		for(;i+1<top[beg]&&(p[i+1].y-p[i].y)*B[k]>-(p[i+1].x-p[i].x)*A[k];i++);
		f[k]=max(f[k],p[i].x*A[k]+p[i].y*B[k]);
	}
	solve(mid,end);
	
	
	static vec tmp[N];
	merge(p+beg,p+top[beg],p+mid,p+top[mid],tmp,cmpxy);
	int cnt=top[beg]-beg+top[mid]-mid;
	top[beg]=beg;
	for(int i=0;i<cnt;i++){
		while(top[beg]-beg>=2&&cross(p[top[beg]-2],p[top[beg]-1],tmp[i])<0)
			top[beg]--;
		if(!close(p[top[beg]-1],tmp[i]))
			p[top[beg]++]=tmp[i];
	}
}

int main(){
	scanf("%d%lf",&n,f);
	for(int i=1;i<=n;i++) scanf("%lf%lf%lf",A+i,B+i,Rate+i);
	geto(0,n+1,ord);
	solve(0,n+1);
	printf("%.3lf\n",f[n]);
}

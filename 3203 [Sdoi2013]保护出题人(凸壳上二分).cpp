#include <cstdio>

const int N=(int)1e5+5;
const double inf=1e40;

int n,top,s[N];
double d,a[N],x[N],sum[N];

#define cross(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

int main(){
	scanf("%d%lf",&n,&d);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i],&x[i]);
	for(int i=n;i>=1;i--)
		sum[i]=sum[i+1]+a[i];
	sum[n+2]=-inf;
	double ans=0;
	for(int i=1;i<=n;i++){
		double x0=x[i]+d*i;
		while(top>=2&&cross(-d*(s[top]-i),sum[s[top]]-sum[i],-d*(s[top-1]-i),sum[s[top-1]]-sum[i])>=0) top--;
		s[++top]=i;
		s[0]=s[1];
		s[top+1]=n+2;
		int l=0,r=top;
		while(r-l>1){
			int mid=l+r>>1;
			if(cross(x0-d*s[mid+1],sum[s[mid+1]]-sum[i+1],x0-d*s[mid],sum[s[mid]]-sum[i+1])<0)
				l=mid;
			else
				r=mid;
		}
		ans+=(sum[s[r]]-sum[i+1])/(x0-d*s[r]);
	}
	printf("%.0lf\n",ans);
}

#include <cstdio>
#include <cmath>
typedef double db;
const db eps=1e-6;
const int N=8;
int n,m;
struct vec{
	db x,y;
} t[1<<N];
bool f[1<<N];
struct line{
	db a,b,c;
	void read(){
		db x1,y1,x2,y2; scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		x2-=x1; y2-=y1;
		a=y2;
		b=-x2;
		c=y1*x2-x1*y2;
		db k=sqrt(a*a+b*b);
		a/=k;
		b/=k;
		c/=k;
	}
} a[N];
int main(){
	scanf("%d",&n);
	for(int i=n-1;i>=0;i--) a[i].read();
	scanf("%d",&m);
	while(m--){
		scanf("%lf%lf",&t[0].x,&t[0].y);
		f[0]=0;
		for(int j=0;j<n;j++)
			for(int i=0;i<1<<j;i++) if(f[i]) f[i|1<<j]=1; else{
				db len=a[j].a*t[i].x+a[j].b*t[i].y+a[j].c;
				if(len>-eps) f[i]=f[i|1<<j]=1; else{
					f[i|1<<j]=0;
					t[i|1<<j].x=t[i].x-2*len*a[j].a;
					t[i|1<<j].y=t[i].y-2*len*a[j].b;
				}
			}
		int ans=0;
		for(int i=0;i<1<<n;i++)
			ans+=!f[i]&&t[i].x>eps&&t[i].x<100-eps&&t[i].y>eps&&t[i].y<100-eps;
		printf("%d\n",ans);
	}
}

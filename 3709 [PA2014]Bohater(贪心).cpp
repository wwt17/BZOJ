#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=100005;
int n,i;
ll z;
struct data{
	int x,y,loc;
} a[N];
inline bool cmpx(const data &a,const data &b){
	return a.x<b.x;
}
inline bool cmpy(const data &a,const data &b){
	return a.y>b.y;
}
int ans[N];
int main(){
	scanf("%d%lld",&n,&z);
	for(i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].loc=i+1;
	sort(a,a+n,cmpx);
	for(i=0;i<n;i++) if(a[i].y>=a[i].x)
		if(a[i].x<z) z+=a[i].y-a[i].x,ans[++*ans]=a[i].loc;
		else{ puts("NIE"); return 0; }
	sort(a,a+n,cmpy);
	for(i=0;i<n;i++) if(a[i].y<a[i].x)
		if(a[i].x<z) z+=a[i].y-a[i].x,ans[++*ans]=a[i].loc;
		else{ puts("NIE"); return 0; }
	puts("TAK");
	for(int i=1;i<*ans;i++) printf("%d ",ans[i]); printf("%d\n",ans[*ans]);
}

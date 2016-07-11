#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005;
int n,x1[N],x2[N],y1[N],y2[N];

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		*x1=*y1=1e9;
		*x2=*y2=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d%d%d",x1+i,x2+i,y1+i,y2+i);
			*x1=min(*x1,x1[i]);
			*x2=max(*x2,x2[i]);
			*y1=min(*y1,y1[i]);
			*y2=max(*y2,y2[i]);
		}
		bool ok=0;
		for(int i=1;i<=n;i++)
			if(*x1==x1[i]&&*x2==x2[i]&&*y1==y1[i]&&*y2==y2[i]){
				ok=1;
				break;
			}
		puts(ok?"TAK":"NIE");
	}
}

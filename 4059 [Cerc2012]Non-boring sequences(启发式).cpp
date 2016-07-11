#include <cstdio>
#include <algorithm>
using namespace std;

const int N=200005;

int n,a[N],b[N],las[N],nex[N];

bool work(int beg,int end){
	if(beg==end) return true;
	int mid=-1;
	for(int l=beg,r=end-1,f=0;l<=r;f^=1)
		if(!f){
			if(las[l]<beg&&nex[l]>=end){
				mid=l;
				break;
			}
			l++;
		}
		else{
			if(las[r]<beg&&nex[r]>=end){
				mid=r;
				break;
			}
			r--;
		}
	if(mid==-1) return false;
	return work(beg,mid)&&work(mid+1,end);
}

bool Main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]),b[i]=a[i];
	sort(b,b+n);
	int m=unique(b,b+n)-b;
	for(int i=0;i<n;i++) a[i]=lower_bound(b,b+m,a[i])-b;
	for(int i=0;i<n;i++) b[i]=-1;
	for(int i=0;i<n;i++){
		las[i]=b[a[i]];
		b[a[i]]=i;
	}
	for(int i=0;i<n;i++) b[i]=n;
	for(int i=n-1;i>=0;i--){
		nex[i]=b[a[i]];
		b[a[i]]=i;
	}
	return work(0,n);
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		puts(Main()?"non-boring":"boring");
}

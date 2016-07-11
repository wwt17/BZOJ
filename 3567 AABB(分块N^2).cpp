#include <cstdio>
typedef long long ll;
const int N=31005,S=200;
struct rec{
	short x1,y1,x2,y2;
} a[N];
inline bool inter(rec &a,rec &b){
	return a.x1<b.x2&&b.x1<a.x2&&a.y1<b.y2&&b.y1<a.y2;
}
int s[S][N],t[N][S];
int n,size,q;
ll l1,r1,l2,r2;
inline ll work(int x,int y){
	ll ans=0;
	for(int i=0;i<x/size;i++) ans+=s[i][y];
	for(int i=x/size*size;i<x;i++){
		ans+=t[i][y/size];
		for(int j=y/size*size;j<y;j++) ans+=inter(a[i],a[j]);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(size=0;size*size<n;size++);
	for(int i=0;i<n;i++) scanf("%hd%hd%hd%hd",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
	for(int j=0,jj=0;j<n;j+=size,jj++)
		for(int i=0;i<n;i++){
			int f=0;
			for(int k=0;k<size;k++) f+=inter(a[j+k],a[i]);
			s[jj][i+1]=s[jj][i]+f;
			t[i][jj+1]=t[i][jj]+f;
		}
	scanf("%d",&q);
	ll ans=0;
	while(q--){
		scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
		l1^=ans; r1^=ans; l2^=ans; r2^=ans;
		l1--; l2--;
		printf("%lld\n",ans=work(l1,l2)-work(l1,r2)-work(r1,l2)+work(r1,r2));
	}
}

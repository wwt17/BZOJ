#include <cstdio>
#include <algorithm>
using namespace std;
const int K=1000005,p1=7,p2=2848631,P=p1*p2;
int n,k,p,inv[p2],frac[p2];
struct data{
	int x,y;
	bool operator < (const data &b) const{
		return x<b.x;
	}
} f[K];
inline int C(int n,int m){
	long long ans=1;
	for(;n||m;n/=p,m/=p){
		int a=n%p,b=m%p;
		if(a<b) return 0;
		ans=ans*frac[a]%p*inv[(long long)frac[a-b]*frac[b]%p]%p;
	}
	return ans;
}
inline int count(int x1,int y1,int x2,int y2){
	int u=(x2+y2-x1-y1)/2;
	if(u<0||x2-x1-u<0) return 0;
	return C(x2-x1,u);
}
int calc(){
	frac[0]=1;
	for(int i=1;i<p;i++) frac[i]=(long long)frac[i-1]*i%p;
	inv[1]=1;
	for(int i=2;i<p;i++) inv[i]=(p-p/i)*(long long)inv[p%i]%p;
	long long ans=1;
	for(int i=0;i<k;i++){
		ans*=p+count(f[i].x,f[i].y,f[i+1].x,f[i+1].y)-count(f[i].x,-2-f[i].y,f[i+1].x,f[i+1].y);
		ans%=p;
	}
	return ans;
}
int h(){
	int ans=0;
	for(int i=0;i<k;i++){
		int u=(f[i+1].x+f[i+1].y-f[i].x-f[i].y)/2;
		ans=max(ans,f[i].y+u);
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	f[0].x=0;
	f[0].y=0;
	for(int i=1;i<=k;i++) scanf("%d%d",&f[i].x,&f[i].y);
	k++;
	f[k].x=n;
	f[k].y=0;
	sort(f+1,f+k);
	p=p1;
	int a1=calc(),t1=inv[p2%p1];
	p=p2;
	int a2=calc(),t2=inv[p1%p2];
	printf("%d %d\n",(int)(((long long)a1*t1%P*p2+(long long)a2*t2%P*p1)%P),h());
}

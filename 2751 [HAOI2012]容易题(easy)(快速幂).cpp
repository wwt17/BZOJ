#include <cstdio>
#include <algorithm>
using namespace std;
const int P=1000000007;
int n,m,k,i,j; long long Ans=1,f,F;
pair<int,int> a[100000];
inline bool cmp(const pair<int,int> a,const pair<int,int> b){
	return a.first<b.first||a.first==b.first&&a.second<b.second;
}
int main(){
	scanf("%u%u%u",&n,&m,&k);
	F=(long long)(1+n)*n/2;
	for(i=0;i<k;i++) scanf("%u%u",&a[i].first,&a[i].second);
	sort(a,a+k,cmp);
	for(i=0;i<k;i=j){
		f=F;
		for(j=i;a[i].first==a[j].first;j++)
			if(j==i||a[j-1].second!=a[j].second) f-=a[j].second;
		Ans=Ans*(f%P)%P;
		m--;
	}
	for(f=F%P;m;m>>=1,f=f*f%P)
		if(m&1) Ans=Ans*f%P;
	printf("%u\n",Ans);
}

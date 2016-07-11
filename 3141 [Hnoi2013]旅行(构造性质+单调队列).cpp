#include <cstdio>
#include <cstdlib>
#include <list>
#include <algorithm>
using namespace std;

const int N=500005;

int n,m,d,a[N],s[N];

list<int> lis[N*2],q[N*2];

inline int calc(int n,int m){
	return max(1,abs(n/m)+bool(n%m));
}

int main(){
	scanf("%d%d",&n,&m);
	int cnt0=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&s[i]);
		s[i]=(s[i]?1:-1)+s[i-1];
		lis[s[i]+n].push_back(i);
		if(s[i]==0) cnt0++;
	}
	if(s[n]==0&&cnt0>=m){
		int j=n;
		for(int i=0;m>1;m--){
			int ii=0;
			while(!lis[j].empty()&&cnt0>=m){
				while(!q[j].empty()&&a[q[j].back()]>a[lis[j].front()]) q[j].pop_back();
				q[j].push_back(lis[j].front());
				lis[j].pop_front();
				cnt0--;
			}
			while(!q[j].empty()&&q[j].front()<=i) q[j].pop_front();
			if(!q[j].empty())
				if(!ii||a[q[j].front()]<a[ii]) ii=q[j].front();
			printf("%d ",a[ii]);
			i=ii;
		}
		printf("%d\n",a[n]);
	}
	else{
		d=calc(s[n],m);
		for(int i=0;m>1;m--){
			int ii=0;
			for(int j=max(-n,s[i]-d);j<=min(n,s[i]+d);j++) if(calc(s[n]-j,m-1)<=d){
				j+=n;
				while(!lis[j].empty()&&lis[j].front()<=n-(m-1)){
					while(!q[j].empty()&&a[q[j].back()]>a[lis[j].front()]) q[j].pop_back();
					q[j].push_back(lis[j].front());
					lis[j].pop_front();
				}
				while(!q[j].empty()&&q[j].front()<=i) q[j].pop_front();
				if(!q[j].empty())
					if(!ii||a[q[j].front()]<a[ii]) ii=q[j].front();
				j-=n;
			}
			printf("%d ",a[ii]);
			i=ii;
		}
		printf("%d\n",a[n]);
	}
}

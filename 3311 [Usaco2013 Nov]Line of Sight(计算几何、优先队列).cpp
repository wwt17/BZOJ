#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
const double PI=acos(-1);
int n,r;
pair<double,double> a[50000];
int main(){
	scanf("%d%d",&n,&r);
	for(int i=0;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		double theta=atan2(y,x),alpha=acos(r/sqrt((double)x*x+(double)y*y));
		if(theta-alpha<0) theta+=2*PI;
		a[i]=make_pair(theta-alpha,theta+alpha);
	}
	sort(a,a+n);
	priority_queue<double,vector<double>,greater<double> > q;
	int result=0;
	for(int iters=0;iters<2;iters++)
		for(int i=0;i<n;i++){
			while(!q.empty()&&q.top()<a[i].first) q.pop();
			if(iters) result+=q.size();
			q.push(a[i].second);
			a[i].first+=2*PI;
			a[i].second+=2*PI;
		}
	printf("%d\n",result);
}

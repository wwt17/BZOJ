#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=50000;
int n,d,cnt;
struct data{
	int x,h;
	bool operator < (const data b)const{
		return x<b.x;
	}
} a[N];
deque<data> s;
bool f[N];
int main(){
	scanf("%d%d",&n,&d);
	for(int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].h);
	sort(a,a+n);
	for(int i=0;i<n;i++){
		for(;!s.empty()&&s.begin()->x<a[i].x-d;s.pop_front());
		f[i]=!s.empty()&&s.begin()->h>=a[i].h*2;
		for(;!s.empty()&&(s.end()-1)->h<=a[i].h;s.pop_back());
		s.push_back(a[i]);
	}
	s.clear();
	for(int i=n;i--;){
		for(;!s.empty()&&s.begin()->x>a[i].x+d;s.pop_front());
		if(f[i]&&!s.empty()&&s.begin()->h>=a[i].h*2) cnt++;
		for(;!s.empty()&&(s.end()-1)->h<=a[i].h;s.pop_back());
		s.push_back(a[i]);
	}
	printf("%d\n",cnt);
}

#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001;
int n;
struct sta{
	int a,b;
	void read(){
		scanf("%d%d",&a,&b); b=n-b;
	}
	bool operator < (const sta &t)const{
		return b<t.b||b==t.b&&a<t.a;
	}
	bool operator == (sta t){
		return a==t.a&&b==t.b;
	}
} s[N];
int f[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) s[i].read();
	sort(s,s+n);
	int k=0;
	for(int i=0,j;i<n;i=j){
		for(;k<s[i].b;f[k+1]=f[k],k++);
		for(j=i+1;j<n&&s[j]==s[i];j++);
		int v=j-i<s[i].b-s[i].a?j-i:s[i].b-s[i].a;
		if(v>0&&f[s[i].b]<f[s[i].a]+v)
			f[s[i].b]=f[s[i].a]+v;
	}
	printf("%d\n",n-f[k]);
}

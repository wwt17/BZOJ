#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef long long ll;

const int mo=(int)1e9+7;

const int N=(int)1e6+5;

int n,q;

int belong[2][N];
set<int> s[2][N];
map<int,int> a[2][N];

ll ans=0;

int Main(){
	int ret=0;
	scanf("%d%d",&n,&q);
	ans=0;
	for(int i=1;i<=n;i++)
		for(int t=0;t<=1;t++){
			belong[t][i]=i;
			s[t][i].clear();
			s[t][i].insert(i);
			a[t][i].clear();
			a[t][i][i]++;
		}
	for(int tim=1;tim<=q;tim++){
		int t,x,y; scanf("%d%d%d",&t,&x,&y); t--;
		x=belong[t][x];
		y=belong[t][y];
		if(x!=y){
			if(s[t][x].size()>s[t][y].size()) swap(x,y);
			for(map<int,int>::iterator cur=a[t][x].begin();cur!=a[t][x].end();a[t][x].erase(cur++)){
				if(a[t][y].find(cur->first)!=a[t][y].end())
					ans+=1LL*cur->second*a[t][y][cur->first];
				a[t][y][cur->first]+=cur->second;
			}
			for(set<int>::iterator cur=s[t][x].begin();cur!=s[t][x].end();s[t][x].erase(cur++)){
				if(!--a[t^1][belong[t^1][*cur]][x]) a[t^1][belong[t^1][*cur]].erase(x);
				a[t^1][belong[t^1][*cur]][belong[t][*cur]=y]++;
				s[t][y].insert(*cur);
			}
		}
		ret=(ret+ans*tim)%mo;
	}
	return ret;
}

int main(){
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}

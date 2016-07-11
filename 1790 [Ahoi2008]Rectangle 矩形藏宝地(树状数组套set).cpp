#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int N=200001;

int n,ord[N];
struct data{
	int x1,y1,x2,y2;
	bool operator < (const data b) const{
		return x1<b.x1;
	}
} a[N];
typedef pair<int,int> pii;
set<pii> t[N];
void insert(set<pii> &S,pii p){
	set<pii>::iterator it=S.insert(p).first;
	if(++it!=S.end()&&p.second<=it->second){
		S.erase(p);
		return;
	}
	while((it=S.find(p))!=S.begin()){
		it--;
		if(it->second<=p.second)
			S.erase(it);
		else break;
	}
}
int query(set<pii> &S,int a){
	set<pii>::iterator it=S.lower_bound(pii(a,0));
	if(it==S.end()) return 0;
	return it->second;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d%d",
			&a[i].x1,
			&a[i].y1,
			&a[i].x2,
			&a[i].y2),
		ord[i]=a[i].y1;
	sort(a,a+n);
	sort(ord,ord+n);
	int ans=0;
	for(int i=0;i<n;i++){
		a[i].y1=lower_bound(ord,ord+n,a[i].y1)-ord+1;
		for(int x=a[i].y1;x<=n;x+=x&-x)
			insert(t[x],pii(a[i].x2,a[i].y2));
		for(int x=a[i].y1-1;x;x-=x&-x)
			if(query(t[x],a[i].x2)>a[i].y2){
				ans++;
				break;
			}
	}
	printf("%d\n",ans);
}

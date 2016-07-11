#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pii;
const int N=200005,logN=18,inf=(int)1e9+5;
int n,m,ans;
struct data *null;
struct data{
	int st,en;
	bool ok;
	data *next[logN];
} nul,a[N],*ord[N],*ord2[N];
bool cmp(const data *a,const data *b){
	return a->st<b->st||a->st==b->st&&a->en>b->en;
}
set<pii> s;
int calc(int l,int r){
	int x=0;
	data tmp;
	tmp.st=l;
	tmp.en=inf;
	data *u=*lower_bound(ord2,ord2+m,&tmp,cmp);
	if(u==null||u->en>r) return 0;
	x=1;
	for(int j=logN-1;j>=0;j--) if(u->next[j]->en<=r)
		x+=1<<j,u=u->next[j];
	return x;
}
int main(){
	null=&nul;
	for(int j=0;j<logN;j++) null->next[j]=null;
	null->st=-2*inf;
	null->en=2*inf;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].st,&a[i].en);
		ord[i]=a+i;
	}
	sort(ord,ord+n,cmp);
	for(int i=0;i<n;i++) ord[i]->ok=1;
	for(int i=n-1,now=inf;i>=0;i--){
		if(now<=ord[i]->en){
			ord[i]->ok=0;
		}
		else
			now=ord[i]->en;
	}
	for(int i=0;i<n;i++) if(ord[i]->ok) ord2[m++]=ord[i];
	ord2[m]=null;
	for(int i=m-1;i>=0;i--){
		data tmp;
		tmp.st=ord2[i]->en+1;
		tmp.en=inf;
		ord2[i]->next[0]=*lower_bound(ord2+i,ord2+m,&tmp,cmp);
		for(int j=1;j<logN;j++)
			ord2[i]->next[j]=ord2[i]->next[j-1]->next[j-1];
	}
	for(data *u=ord2[0];u!=null;u=u->next[0]) ans++;
	printf("%d\n",ans);
	s.insert(pii(-inf,inf));
	for(int i=0;i<n;i++){
		set<pii>::iterator j=s.upper_bound(pii(a[i].st,inf));
		if(j==s.begin()) continue;
		j--;
		pii t=*j;
		if(t.second<a[i].en) continue;
		if(calc(t.first,a[i].st-1)+1+calc(a[i].en+1,t.second)==calc(t.first,t.second)){
			printf("%d ",i+1);
			s.erase(j);
			s.insert(pii(t.first,a[i].st-1));
			s.insert(pii(a[i].en+1,t.second));
		}
	}
	puts("");
}

#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001;

int n,m,a[N],t[N];
struct tree{
	tree *l,*r; int sum;
} mem[10000001],*newtree=mem,*s[N];
int num;
void insert(tree*&root,int begin,int end){
	if(!root) root=newtree++;
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid) insert(root->l,begin,mid);
		else insert(root->r,mid,end);
	}
	root->sum++;
}
void erase(tree*&root,int begin,int end){
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid) erase(root->l,begin,mid);
		else erase(root->r,mid,end);
	}
	root->sum--;
}
int count(tree* root,int begin,int end){
	if(!root) return 0;
	if(num<=begin) return 0;
	if(num>=end) return root->sum;
	int mid=(begin+end)/2;
	return count(root->l,begin,mid)+count(root->r,mid,end);
}

int main(){
	scanf("%d%d",&n,&m);
	int i;
	for(i=1;i<=n;i++){
		scanf("%d",&num);
		a[num]=i;
	}
	long long ans=0;
	for(i=1;i<=n;i++){
		ans+=i;
		num=a[i];
		for(int x=num;x<=n;x+=x&-x) t[x]++;
		for(int x=num;x;x-=x&-x) ans-=t[x];
		for(int x=i;x<=n;x+=x&-x) insert(s[x],1,n+1);
	}
	while(m--){
		printf("%lld\n",ans);
		scanf("%d",&i);
		num=a[i];
		for(int x=i;x<=n;x+=x&-x) erase(s[x],1,n+1);
		for(int x=i;x;x-=x&-x) ans-=(s[x]?s[x]->sum:0)-2*count(s[x],1,n+1);
		for(int x=n;x;x-=x&-x) ans-=count(s[x],1,n+1);
	}
}

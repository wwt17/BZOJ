#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100001,M=1000001;

int n,m,R,a[N],o[N],pre[N];

struct tree{
	tree *l,*r;
	int sum;
	tree():l(NULL),r(NULL),sum(0){
	}
	~tree(){
		if(l!=NULL) delete l;
		if(r!=NULL) delete r;
	}
} *s[N],*t[N];

int num,numl,numr;
void insert(tree*&root,int begin,int end){
	if(root==NULL) root=new tree;
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid)
			insert(root->l,begin,mid);
		else
			insert(root->r,mid,end);
	}
	root->sum++;
}
void erase(tree*&root,int begin,int end){
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid)
			erase(root->l,begin,mid);
		else
			erase(root->r,mid,end);
	}
	if(!--root->sum){
		delete root;
		root=NULL;
	}
}
int count(tree* root,int begin,int end){
	if(root==NULL) return 0;
	if(numl<=begin&&numr>=end) return root->sum;
	int mid=(begin+end)/2;
	if(numr<=mid) return count(root->l,begin,mid);
	if(numl>=mid) return count(root->r,mid,end);
	return count(root->l,begin,mid)+count(root->r,mid,end);
}

struct query{
	int l,r,a,b,ans1,ans2;
	inline void read(){
		scanf("%d%d%d%d",&l,&r,&a,&b);
		l--;
		a=lower_bound(o,o+R,a)-o;
		b=lower_bound(o,o+R,b+1)-o;
	}
	bool operator < (query B) const{
		return r<B.r;
	}
} q[M],*ord[M];
bool cmp(query *A,query *B){
	return A->r < B->r;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i),o[i-1]=a[i];
	sort(o,o+n);
	R=unique(o,o+n)-o;
	for(int i=1;i<=n;i++) a[i]=lower_bound(o,o+R,a[i])-o;
	for(int j=0;j<m;j++) q[j].read(),ord[j]=q+j;
	sort(ord,ord+m,cmp);
	for(int j=0,i=0;j<m;j++){
		for(;i<ord[j]->r;){
			i++;
			num=a[i];
			for(int x=i;x<=n;x+=x&-x) insert(s[x],0,R),insert(t[x],0,R);
			if(pre[a[i]])
				for(int x=pre[a[i]];x<=n;x+=x&-x) erase(t[x],0,R);
			pre[a[i]]=i;
		}
		numl=ord[j]->a;
		numr=ord[j]->b;
		int ans1=0,ans2=0;
		for(int x=ord[j]->r;x;x-=x&-x)
			ans1+=count(s[x],0,R),
			ans2+=count(t[x],0,R);
		for(int x=ord[j]->l;x;x-=x&-x)
			ans1-=count(s[x],0,R),
			ans2-=count(t[x],0,R);
		ord[j]->ans1=ans1;
		ord[j]->ans2=ans2;
	}
	for(int j=0;j<m;j++) printf("%d %d\n",q[j].ans1,q[j].ans2);
}

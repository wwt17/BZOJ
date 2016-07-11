#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N=2000005;

int n,m,ans=0;

struct node{
	int val;
	vector<node*> son;
} V[N];

bool cmp(const node *u,const node *v){
	return u->val<v->val;
}

void dfs(node *u){
	for(vector<node*>::iterator e=u->son.begin();e!=u->son.end();e++)
		dfs(*e);
	sort(u->son.begin(),u->son.end(),cmp);
	for(vector<node*>::iterator e=u->son.begin();e!=u->son.end();e++){
		node *v=*e;
		if(u->val+v->val-1>m) break;
		u->val+=v->val-1;
		ans++;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&V[i].val);
	for(int i=0;i<n;i++){
		int k; scanf("%d",&k);
		while(k--){
			int j; scanf("%d",&j);
			V[i].son.push_back(V+j);
			V[i].val++;
		}
	}
	dfs(V);
	printf("%d\n",ans);
}

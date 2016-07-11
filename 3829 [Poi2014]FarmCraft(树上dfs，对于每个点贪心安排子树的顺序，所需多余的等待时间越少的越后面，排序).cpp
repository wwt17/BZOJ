#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N=500005;
int n;
struct node{
	node *pa;
	vector<node*> son;
	int c,s,f;
	void dfs();
} V[N];
bool cmp(const node *u,const node *v){
	return u->f<v->f;
}
void node::dfs(){
	for(vector<node*>::iterator e=son.begin();e!=son.end();)
		if(*e==pa){
			son.erase(e);
		}
		else{
			node *v=*e;
			v->pa=this;
			v->dfs();
			e++;
		}
	sort(son.begin(),son.end(),cmp);
	for(vector<node*>::iterator e=son.begin();e!=son.end();e++){
		f=max(f,(*e)->f-1-s);
		s+=2+(*e)->s;
	}
	if(pa) f=max(f,c-s);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].c);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		V[x].son.push_back(V+y);
		V[y].son.push_back(V+x);
	}
	V[1].dfs();
	printf("%d\n",V[1].s+max(V[1].c,V[1].f));
}

#include <cstdio>
#include <vector>
using namespace std;
const int logN=16,N=1<<logN;
int n;
struct node{
	vector<node*> pre;
	int oud,depth,size;
	node *pa[logN],*son,*next;
} V[N],*ord[N],**st=ord,**en=ord;
node *lca(node *u,node *v){
	for(int i=logN-1;i>=0;i--) if(u->pa[i]->depth>=v->depth)
		u=u->pa[i];
	for(int i=logN-1;i>=0;i--) if(v->pa[i]->depth>=u->depth)
		v=v->pa[i];
	for(int i=logN-1;i>=0;i--) if(u->pa[i]!=v->pa[i]) u=u->pa[i],v=v->pa[i];
	if(u!=v) u=u->pa[0];
	return u;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int j; scanf("%d",&j);
		while(j){
			V[i].pre.push_back(V+j);
			V[j].oud++;
			scanf("%d",&j);
		}
		if(V[i].pre.size()==0)
			V[i].pre.push_back(V),V[0].oud++;
	}
	for(int i=0;i<=n;i++) if(!V[i].oud) *en++=V+i;
	while(st<en){
		node *u=*st++;
		for(vector<node*>::iterator it=u->pre.begin();it!=u->pre.end();it++){
			node *v=*it;
			if(!--v->oud)
				*en++=v;
		}
	}
	V->pre.push_back(V);
	for(node **i=en-1;i>=ord;i--){
		node *u=*i,*v=*u->pre.begin();
		for(vector<node*>::iterator it=++u->pre.begin();it!=u->pre.end();it++)
			v=lca(v,*it);
		u->pa[0]=v;
		u->next=v->son;
		v->son=u;
		u->depth=v->depth+1;
		for(int i=1;i<logN;i++)
			u->pa[i]=u->pa[i-1]->pa[i-1];
	}
	for(node **i=ord;i<en;i++){
		node *u=*i;
		for(node *v=u->son;v;v=v->next) u->size+=v->size;
		u->size++;
	}
	for(int i=1;i<=n;i++) printf("%d\n",V[i].size-1);
	scanf("\n");
}

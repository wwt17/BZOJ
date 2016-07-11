#include <cstdio>
#include <vector>
using namespace std;
const int N=100005,logN=18;
int n,m;
inline void buildt(vector<int> &s){
	s.push_back(0);
	for(int i=s.size()-1;i;i--) s[i]=s[i-1];
	s[0]=0;
	for(int i=1;i<s.size();i++) if(i+(i&-i)<s.size())
		s[i+(i&-i)]+=s[i];
}
inline int query(vector<int> &s,int x){
	if(x<0) return 0;
	x++;
	if(x>s.size()-1) x=s.size()-1;
	int ans=0;
	for(;x;x-=x&-x) ans+=s[x];
	return ans;
}
inline void modify(vector<int> &s,int x,int val){
	x++;
	for(;x<s.size();x+=x&-x) s[x]+=val;
}
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	node *boss;
	edge *son;
	int size,level,dist[logN];
	vector<int> s,t;
	void getsize(node *pa){
		size=1;
		for(edge *e=son;e;e=e->next) if(!e->ed->boss&&e->ed!=pa){
			e->ed->getsize(this);
			size+=e->ed->size;
		}
	}
	node* getroot(){
		node *v=NULL;
		for(edge *e=son;e;e=e->next) if(!e->ed->boss)
			if(!v||e->ed->size>v->size) v=e->ed;
		if(!v||v->size*2<=size) return this;
		int t=size-v->size;
		v->size+=t;
		size=t;
		return v->getroot();
	}
	void getdist(node *pa,int Level,int Dist,vector<int> &t){
		dist[Level]=Dist;
		for(;t.size()<Dist+1;t.push_back(0));
		t[Dist]+=s[1];
		for(edge *e=son;e;e=e->next) if(e->ed->level>Level&&e->ed!=pa)
			e->ed->getdist(this,Level,Dist+1,t);
	}
	node* build(node *Boss,int Level){
		getsize(NULL);
		node *root=getroot();
		root->boss=Boss;
		root->level=Level;
		for(edge *e=root->son;e;e=e->next) if(!e->ed->boss){
			node *v=e->ed->build(root,Level+1);
			e->ed->getdist(root,Level,1,v->t);
			for(;root->s.size()<v->t.size();root->s.push_back(0));
			for(int i=0;i<v->t.size();i++) root->s[i]+=v->t[i];
			buildt(v->t);
		}
		buildt(root->s);
		return root;
	}
} V[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int val; scanf("%d",&val);
		V[i].s.push_back(val);
	}
	for(int i=1;i<n;i++){
		int u,v; scanf("%d%d",&u,&v);
		*newE=(edge){V+v,V[u].son},V[u].son=newE++;
		*newE=(edge){V+u,V[v].son},V[v].son=newE++;
	}
	V[1].build(V,0);
	int lastans=0;
	while(m--){
		int type,x; scanf("%d%d",&type,&x);
		x^=lastans;
		if(type==0){
			int k; scanf("%d",&k); k^=lastans;
			lastans=query(V[x].s,k);
			for(node *u=V+x;u->boss!=V;u=u->boss)
				lastans+=query(u->boss->s,k-V[x].dist[u->boss->level])-query(u->t,k-V[x].dist[u->boss->level]);
			printf("%d\n",lastans);
		}
		else{
			int val; scanf("%d",&val); val^=lastans;
			val-=V[x].s[1];
			modify(V[x].s,0,val);
			for(node *u=V+x;u->boss!=V;u=u->boss){
				modify(u->boss->s,V[x].dist[u->boss->level],val);
				modify(u->t,V[x].dist[u->boss->level],val);
			}
		}
	}
}

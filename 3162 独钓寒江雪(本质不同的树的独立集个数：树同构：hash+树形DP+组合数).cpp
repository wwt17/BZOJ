#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int N=500005,mo=(int)1e9+7,base=55566677;

int n,inv[N],pwbase[N*2];

void init(){
	inv[1]=1;
	for(int i=2;i<=n;i++) inv[i]=ll(mo-mo/i)*inv[mo%i]%mo;
	pwbase[0]=1;
	for(int i=1;i<=n*2;i++) pwbase[i]=pwbase[i-1]*base;
}

ll C(ll n,int m){
	n%=mo;
	ll ans=1;
	for(int i=1;i<=m;i++)
		ans=ans*(n-i+1)%mo*inv[i]%mo;
	return ans;
}

struct node;
bool cmp(node *u,node *v);
struct node{
	vector<node*> son;
	typedef vector<node*>::iterator edge;
	int size,hash,hlen;
	ll f,g;
	void addedge(node *v){
		son.push_back(v);
	}
	void deledge(node *v){
		for(edge e=son.begin();e!=son.end();e++) if(*e==v){
			son.erase(e);
			break;
		}
	}
	void getsize(node *fa){
		size=1;
		for(edge e=son.begin();e!=son.end();e++){
			node *v=*e;
			if(v==fa) continue;
			v->getsize(this);
			size+=v->size;
		}
	}
	void dp(node *fa){
		deledge(fa);
		for(edge e=son.begin();e!=son.end();e++){
			node *v=*e;
			v->dp(this);
		}
		sort(son.begin(),son.end(),cmp);
		f=g=1;
		for(edge i=son.begin(),j=i;i!=son.end();i=j){
			node *v=*i;
			for(;j!=son.end()&&v->hash==(*j)->hash;j++);
			int len=j-i;
			f=f*C(v->f+v->g+len-1,len)%mo;
			g=g*C(v->f+len-1,len)%mo;
		}
		hash=1;
		hlen=1;
		for(edge e=son.begin();e!=son.end();e++){
			node *v=*e;
			hash=hash*pwbase[v->hlen]+v->hash;
			hlen+=v->hlen;
		}
		hash=hash*base+2;
		hlen++;
	}
} *root,*root1,*root2,V[N];
bool cmp(node *u,node *v){
	return u->hash<v->hash;
}

node *getroot(node *u){
	for(;;){
		node *v=NULL;
		for(node::edge e=u->son.begin();e!=u->son.end();e++) if((*e)->size*2>u->size){
			v=*e;
			break;
		}
		if(!v) break;
		int tmp=u->size;
		u->size-=v->size;
		v->size=tmp;
		u=v;
	}
	return u;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		V[x].addedge(V+y);
		V[y].addedge(V+x);
	}
	V[1].getsize(NULL);
	root=getroot(V+1);
	for(node::edge e=root->son.begin();e!=root->son.end();e++) if((*e)->size*2==root->size){
		root1=root,root2=*e;
		root1->deledge(root2);
		root2->deledge(root1);
		root=V+(++n);
		root->addedge(root1);
		root->addedge(root2);
		break;
	}
	init();
	root->dp(NULL);
	ll ans=0;
	if(root2){
		if(root1->hash==root2->hash){
			ans=(C(root1->f+2-1,2)+root1->f*root1->g%mo)%mo;
		}
		else{
			ans=(root1->f*root2->f%mo+root1->f*root2->g%mo+root1->g*root2->f%mo)%mo;
		}
	}
	else{
		ans=(root->f+root->g)%mo;
	}
	printf("%d\n",int((ans+mo)%mo));
}

#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005,L=2000005,Len=L*2,logLen=22;
int n,m,base,cnt,len,t[Len];

void add(int x,int d){
	for(;x<=cnt;x+=x&-x) t[x]+=d;
}
int query(int x){
	int s=0; for(;x;x-=x&-x) s+=t[x]; return s;
}

char s[L];

struct node;

node *z[1<<logLen|Len];

struct node{
	char c;
	node *son[26],*hea,*nex,*fail;
	int depth,locst,locen,st,en;
	void dfs(){
		locst=cnt;
		st=++len;
		z[base|len]=this;
		for(node *v=hea;v;v=v->nex){
			v->depth=depth+1;
			v->dfs();
			++len;
			z[base|len]=this;
		}
		en=len;
		locen=++cnt;
	}
} root[L],*newnode=root+1;

void buildz(){
	for(int l=base>>1,r=(base|len+1)>>1;l^r^1;l>>=1,r>>=1)
		for(int j=l+1;j<r;j++) z[j]=z[j<<1]->depth<z[j<<1|1]->depth?z[j<<1]:z[j<<1|1];
}
node* lca(node *u,node *v){
	int l=base|u->st-1,r=base|v->st+1;
	node *ans=u;
	for(;l^r^1;l>>=1,r>>=1){
		if(!(l&1)) if(z[l^1]->depth<ans->depth) ans=z[l^1];
		if(  r&1 ) if(z[r^1]->depth<ans->depth) ans=z[r^1];
	}
	return ans;
}

void build(){
	static node *q[L];
	int head=0,tail=0;
	root->fail=root;
	q[tail++]=root;
	head++;
	for(int c=0;c<26;c++)
		if(root->son[c]){
			q[tail++]=root->son[c];
			root->son[c]->fail=root;
		}
		else
			root->son[c]=root;
	while(head<tail){
		node *u=q[head++];
		for(int c=0;c<26;c++)
			if(u->son[c]){
				q[tail++]=u->son[c];
				u->son[c]->fail=u->fail->son[c];
			}
			else
				u->son[c]=u->fail->son[c];
	}
	for(int i=1;i<tail;i++){
		node *u=q[i];
		u->nex=u->fail->hea;
		u->fail->hea=u;
	}
	root->dfs();
}

node *ed[N],*seq[L];

bool cmpdfn(node *u,node *v){
	return u->st<v->st;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		node *u=root;
		char *j;
		for(j=s;*j;j++){
			int c=*j-'a';
			if(!u->son[c]) u->son[c]=newnode++;
			u=u->son[c];
		}
		ed[i]=u;
	}
	int le=2*(newnode-root)+2;
	for(base=1;base<=le;base<<=1);
	build();
	buildz();
	int q; scanf("%d",&q);
	while(q--){
		int type; scanf("%d",&type);
		if(type==1){
			scanf("%s",s);
			m=0;
			node *u=root;
			seq[m++]=u;
			for(char *j=s;*j;j++)
				seq[m++]=u=u->son[*j-'a'];
			sort(seq,seq+m,cmpdfn);
			for(int i=0;i<m;i++) add(seq[i]->locen,1);
			for(int i=1;i<m;i++) add(lca(seq[i-1],seq[i])->locen,-1);
		}
		else{
			int x; scanf("%d",&x);
			printf("%d\n",query(ed[x]->locen)-query(ed[x]->locst));
		}
	}
}

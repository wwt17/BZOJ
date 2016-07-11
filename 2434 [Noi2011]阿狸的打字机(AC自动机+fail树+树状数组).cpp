#include <cstdio>
#include <queue>
using namespace std;
const int N=(int)1e5+5,M=N;
char s[N];
int len,t[N];
int presum(int x){
	int s=0;
	for(;x;x-=x&-x) s+=t[x];
	return s;
}
void add(int x,int d){
	for(;x<=len;x+=x&-x) t[x]+=d;
}
struct query;
struct trie{
	trie *pa,*son[26],*fail,*fson,*fnext;
	query *qson;
	int st,en;
	void buildfail(){
		st=len;
		for(trie *v=fson;v;v=v->fnext) v->buildfail();
		en=++len;
	}
} root[N],*newtrie=root+1;
void build(){
	queue<trie*> q;
	root->fail=root;
	for(int c=0;c<26;c++) if(root->son[c]){
		trie *v=root->son[c];
		v->fail=root;
		v->fnext=root->fson;
		root->fson=v;
		q.push(v);
	}
	while(!q.empty()){
		trie *u=q.front(); q.pop();
		for(int c=0;c<26;c++) if(u->son[c]){
			trie *v=u->son[c],*f=u->fail;
			for(;f!=root&&!f->son[c];f=f->fail);
			if(f->son[c])
				v->fail=f->son[c];
			else
				v->fail=root;
			v->fnext=v->fail->fson;
			v->fail->fson=v;
			q.push(v);
		}
	}
	root->buildfail();
}
int cnt;
trie *end[N];
int m;
struct query{
	trie *x; int ans;
	query *next;
} seq[M];
int main(){
	scanf("%s",s);
	trie *cur=root;
	for(char *i=s;*i;i++){
		if(*i=='B'){
			cur=cur->pa;
			continue;
		}
		if(*i=='P'){
			end[++cnt]=cur;
			continue;
		}
		trie *&v=cur->son[*i-'a'];
		if(!v) v=newtrie++,v->pa=cur;
		cur=v;
	}
	build();
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int x,y; scanf("%d%d",&x,&y);
		seq[i].next=end[y]->qson;
		end[y]->qson=seq+i;
		seq[i].x=end[x];
	}
	cur=root;
	add(cur->en,1);
	for(char *i=s;*i;i++){
		if(*i=='B'){
			add(cur->en,-1);
			cur=cur->pa;
			continue;
		}
		if(*i=='P'){
			for(query *q=cur->qson;q;q=q->next)
				q->ans=presum(q->x->en)-presum(q->x->st);
			continue;
		}
		cur=cur->son[*i-'a'];
		add(cur->en,1);
	}
	for(int i=1;i<=m;i++) printf("%d\n",seq[i].ans);
}

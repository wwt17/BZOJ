#include <cstdio>
#include <cstring>
#include <queue>
struct Trie *root,*null;
struct Trie{
	#define CH 26
	#define get(c) ((c)-'a')
	#define NextChar get(getchar())
	#define EndChar get('\n')
	Trie *c[CH],*fail; int sum,matchsum; bool vis;
	Trie():fail(NULL),sum(0),matchsum(0),vis(false){ memset(c,0,sizeof(c)); }
	Trie* insert(){
		char ch; Trie* p=this;
		while((ch=NextChar)!=EndChar){
			if(!p->c[ch]) p->c[ch]=new Trie;
			p=p->c[ch];
			++p->sum;
		}
		return p;
	}
	void build(){
		std::queue<Trie*> q; Trie *x,*y; char ch;
		fail=null; for (ch=0;ch<CH;++ch) if (!c[ch]) c[ch]=this;
		for (q.push(this);!q.empty();q.pop())
			for (x=q.front(),ch=0;ch<CH;++ch)
				if ((y=x->c[ch])&&y!=this){
					q.push(y);
					y->fail=x->fail->c[ch];
				}else
					x->c[ch]=x->fail->c[ch];
	}
	void selfmatch(){
		if(vis) return;
		vis=true;
		for(Trie* p=this;p!=root;p=p->fail)
			p->matchsum+=sum;
		for(char ch=0;ch<CH;++ch)
			c[ch]->selfmatch();
	}
	void NullInit(){ for (char ch=0;ch<CH;++ch) c[ch]=root; }
} words,*end[201];
int N,i;
int main(){
	scanf("%d\n",&N); root=&words,(null=new Trie)->NullInit();
	for(i=1;i<=N;++i)
		end[i]=words.insert();
	words.build();
	words.selfmatch();
	for(i=1;i<=N;++i)
		printf("%d\n",end[i]->matchsum);
}

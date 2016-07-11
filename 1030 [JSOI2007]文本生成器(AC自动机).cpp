/*
f[i]表示已经生成了i的长度，且后缀是这样的情况数。
fail->f[i]+=f[i]
for c = each CH
 if son[c]
  son[c]->f[i+1]+=f[i]
 else//fail
  son[c]->f[i+1]+=f[i]
要自下而上做
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const short P=10007;
#define inc(a,b) (a=(a+(b))%P)
int N,M;
template<char CH=26>
struct Trie{
	Trie *son[CH],*fail; bool mark; short f[2];
	Trie(){
		memset(this,0,sizeof(Trie));
	}
	template<char NextChar(),bool EndChar(char)>
	Trie* insert(){
		char ch; Trie* p=this;
		while(!EndChar(ch=NextChar())){
			if(!p->son[ch]) p->son[ch]=new Trie;
			p=p->son[ch];
		}
		p->mark=true;
		return p;
	}
	void build(std::vector<Trie*> &q){
		int head=0; Trie *x,*y; char ch;
		fail=new Trie;
		for(ch=0;ch<CH;ch++) fail->son[ch]=this;
		for(ch=0;ch<CH;ch++) if(!son[ch]) son[ch]=this;
		q.push_back(this);
		while(head!=q.size())
			for(x=q[head++],ch=0;ch<CH;++ch)
				if((y=x->son[ch])&&y!=this){
					q.push_back(y);
					y->fail=x->fail->son[ch];
				}
				else
					x->son[ch]=x->fail->son[ch];
		for(int i=0;i<q.size();i++)
			q[i]->mark|=q[i]->fail->mark;
	}
};
typedef Trie<> trie;
#define get(c) ((c)-'A')
inline char nextc(){ return get(getchar()); }
inline bool endc(char c){ return c==get('\n'); }
trie words;
vector<trie*> ord;
typedef vector<trie*>::reverse_iterator trrit;
inline short pow(int a,int b){
	int ret=1;
	for(;b;b>>=1,a=a*a%P)
		if(b&1) ret=ret*a%P;
	return ret;
}
int main(){
	scanf("%u%u\n",&N,&M);
	for(int i=0;i<N;i++)
		words.insert<nextc,endc>();
	words.build(ord);
	bool F=false;
	words.f[F]=1;
	for(int i=0;i<M;i++,F^=1){
		for(trrit it=ord.rbegin();it!=ord.rend();it++)
			(*it)->f[!F]=0;
		for(trrit it=ord.rbegin();it!=ord.rend();it++){
			trie *cur=*it;
			if(cur->mark) continue;
			//inc(cur->fail->f[F],cur->f[F]);
			for(char ch=0;ch<26;ch++)
				inc(cur->son[ch]->f[!F],cur->f[F]);
		}
		/*
		for(trrit it=ord.rbegin();it!=ord.rend();it++)
			printf("%6u",(*it)->mark?0:(*it)->f[!F]);
		putchar('\n');
		*/
	}
	short Ans=0;
	for(trrit it=ord.rbegin();it!=ord.rend();it++)
		if(!(*it)->mark){
			inc(Ans,(*it)->f[F]);
		}
	printf("%hu\n",(pow(26,M)-Ans+P)%P);
}

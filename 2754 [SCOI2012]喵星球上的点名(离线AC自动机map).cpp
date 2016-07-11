#include <cstdio>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int N=20001,M=50000;
typedef vector<int> str;
int n,m;

inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
void read(str &s){
	int l=getint();
	while(l--) s.push_back(getint());
}

struct trie{
	typedef map<int,trie*> sonlist;
	sonlist son; trie *fail; int flag,cnt,done;
	trie():fail(NULL),flag(0),cnt(0),done(0){
	}
	void build(){
		queue<trie*> q;
		fail=this;
		for(sonlist::iterator it=son.begin();it!=son.end();it++){
			it->second->fail=this;
			q.push(it->second);
		}
		while(!q.empty()){
			trie *cur=q.front(); q.pop();
			for(sonlist::iterator it=cur->son.begin();it!=cur->son.end();it++){
				trie *f;
				for(f=cur->fail;;f=f->fail){
					sonlist::iterator tmp=f->son.find(it->first);
					if(tmp!=f->son.end()){
						it->second->fail=tmp->second;
						break;
					}
					if(f==this){
						it->second->fail=this;
						break;
					}
				}
				q.push(it->second);
			}
		}
	}
	/*
	void print(){
		static int dep=0;
		printf("this=%p fail=%p flag=%d cnt=%d done=%d\n",
			this,fail,flag,cnt,done);
		dep++;
		for(sonlist::iterator it=son.begin();it!=son.end();it++){
			for(int i=0;i<dep;i++) printf("   "); printf("%d ",it->first);
			it->second->print();
		}
		dep--;
	}
	*/
} root,*query[M];
struct cat{
	str nam[2];
	int cnt;
} a[N];
int main(){
	n=getint(); m=getint();
	for(int i=1;i<=n;i++){
		read(a[i].nam[0]);
		read(a[i].nam[1]);
	}
	for(int i=0;i<m;i++){
		trie *cur=&root,*next;
		for(int l=getint();l;l--){
			trie *&next=cur->son[getint()];
			if(!next) next=new trie;
			cur=next;
		}
		cur->flag++;
		query[i]=cur;
	}
	root.build();
	//root.print();
	for(int i=1;i<=n;i++)
		for(int o=0;o<2;o++){
			trie *cur=&root;
			for(str::iterator l=a[i].nam[o].begin();l!=a[i].nam[o].end();l++){
				trie::sonlist::iterator tmp;
				for(;;cur=cur->fail){
					if((tmp=cur->son.find(*l))!=cur->son.end()){
						cur=tmp->second;
						break;
					}
					if(cur==&root) break;
				}
				for(trie *f=cur;f->done!=i;f=f->fail){
					f->done=i;
					f->cnt++;
					a[i].cnt+=f->flag;
				}
			}
			//printf("i=%d o=%d a[%d].cnt=%d\n",i,o,i,a[i].cnt); root.print();
		}
	for(int i=0;i<m;i++) printf("%d\n",query[i]->cnt);
	for(int i=1;i<=n;i++) printf("%d%c",a[i].cnt,i<n?' ':'\n');
}

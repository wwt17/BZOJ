#include <cstdio>
const int L=205;
int n,l;
struct trie{
	char c; trie *son,*next; int cnt;
	trie(char c_=0):c(c_),son(NULL),next(NULL),cnt(0){
	}
} root[1];
int main(){
	scanf("%d%d%*d",&n,&l);
	int ans=0;
	while(n--){
		static char s[L];
		scanf("%s",s+1);
		trie *u=root,*v;
		for(int i=1;i<=l;i++){
			trie *nex=NULL;
			for(v=u->son;v;v=v->next) if(v->c==s[i])
				nex=v;
			else{
				trie *uu=v,*vv;
				for(int j=i+1;j<=l;j++){
					for(vv=uu->son;vv;vv=vv->next) if(vv->c==s[j]){
						uu=vv;
						break;
					}
					if(!vv) break;
				}
				ans+=uu->cnt;
			}
			if(!nex){
				nex=new trie(s[i]);
				nex->next=u->son;
				u->son=nex;
			}
			u=nex;
		}
		u->cnt++;
	}
	printf("%d\n",ans);
}

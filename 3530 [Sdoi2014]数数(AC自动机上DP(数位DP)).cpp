#include <cstdio>
#include <cstring>
const int N=1205,L=1505,P=(int)1e9+7;
typedef long long ll;
int n,m;
bool F;
struct trie{
	trie *fail,*son[10];
	bool flag;
	int f[2][2];
	trie(){
		fail=NULL;
		for(int c=0;c<10;c++) son[c]=0;
		flag=false;
		f[F][0]=f[F][1]=0;
	}
} root[1],*ord[L],**end;
void build(){
	trie **beg=end=ord;
	*end++=root;
	while(beg<end){
		trie *cur=*beg++;
		for(int c=0;c<10;c++) if(cur->son[c])
			*end++=cur->son[c];
	}
	root->fail=root;
	for(int c=0;c<10;c++) if(root->son[c])
		root->son[c]->fail=root;
	else
		root->son[c]=root;
	for(trie **i=ord+1;i<end;i++){
		trie *cur=*i;
		cur->flag|=cur->fail->flag;
		for(int c=0;c<10;c++) if(cur->son[c])
			cur->son[c]->fail=cur->fail->son[c];
		else
			cur->son[c]=cur->fail->son[c];
	}
}
char s[N],t[L];
int ans;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) s[i]-='0';
	scanf("%d",&m);
	while(m--){
		scanf("%s",t);
		trie *cur=root;
		for(char *c=t;*c;c++){
			*c-='0';
			if(!cur->son[*c]) cur->son[*c]=new trie;
			cur=cur->son[*c];
		}
		cur->flag=true;
	}
	build();
	for(int j=1;j<=n;F^=1,j++){
		for(trie **i=ord;i<end;i++) (*i)->f[!F][0]=(*i)->f[!F][1]=0;
		if(j==1){
			for(int c=1;c<s[j];c++)
				(root->son[c]->f[!F][1]+=1)%=P;
			(root->son[s[j]]->f[!F][0]+=1)%=P;
		}
		else
			for(int c=1;c<10;c++)
				(root->son[c]->f[!F][1]+=1)%=P;
		for(trie **i=ord;i<end;i++){
			trie *cur=*i;
			for(int c=0;c<10;c++)
				(cur->son[c]->f[!F][1]+=cur->f[F][1])%=P;
			for(int c=0;c<s[j];c++)
				(cur->son[c]->f[!F][1]+=cur->f[F][0])%=P;
			(cur->son[s[j]]->f[!F][0]+=cur->f[F][0])%=P;
		}
		for(trie **i=ord;i<end;i++){
			trie *cur=*i;
			if(cur->flag) cur->f[!F][0]=cur->f[!F][1]=0;
		}
	}
	for(trie **i=ord;i<end;i++){
		trie *cur=*i;
		(ans+=cur->f[F][1]+cur->f[F][0])%=P;
	}
	printf("%d\n",ans);
	scanf("\n");
}

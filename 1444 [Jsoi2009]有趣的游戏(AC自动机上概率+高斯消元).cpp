#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N=10,L=12;

const double eps=1e-6;

int n,l,m,size;

char s[L];

struct trie{
	trie *fail,*son[26];
	bool flag;
} root[N*L],*newtrie=root+1,*end[N];

double p[26],a[N*L][N*L];

trie *insert(char *s){
	trie *u;
	for(u=root;*s;s++){
		if(!u->son[*s-'A'])
			u->son[*s-'A']=newtrie++;
		u=u->son[*s-'A'];
	}
	u->flag=true;
	return u;
}

void build(){
	trie *q[N*L],**head=q,**tail=q;
	for(int j=0;j<m;j++)
		if(root->son[j]){
			*tail++=root->son[j];
			root->son[j]->fail=root;
		}
		else
			root->son[j]=root;
	while(head<tail){
		trie *u=*head++;
		for(int j=0;j<m;j++)
			if(u->son[j]){
				*tail++=u->son[j];
				u->son[j]->fail=u->fail->son[j];
			}
			else{
				trie *v=u;
				while(v!=root&&!v->son[j]) v=v->fail;
				if(v->son[j])
					u->son[j]=v->son[j];
				else
					u->son[j]=root;
			}
	}
}

int main(){
	scanf("%d%d%d",&n,&l,&m);
	for(int j=0;j<m;j++){
		int a,b; scanf("%d%d",&a,&b);
		p[j]=(double)a/b;
	}
	for(int i=0;i<n;i++){
		scanf("%s",s);
		end[i]=insert(s);
	}
	build();
	size=newtrie-root;
	for(int i=0;i<size;i++) a[i][i]=1;
	a[0][size]=1;
	for(int i=0;i<size;i++) if(!root[i].flag)
		for(int j=0;j<m;j++)
			a[root[i].son[j]-root][i]-=p[j];
	for(int i=0;i<size;i++) if(!root[i].flag){
		for(int j=i;j<size;j++) if(fabs(a[j][i])>eps){
			for(int k=i;k<=size;k++) swap(a[i][k],a[j][k]);
			break;
		}
		for(int k=size;k>=i;k--) a[i][k]/=a[i][i];
		for(int j=0;j<size;j++) if(j!=i)
			for(int k=size;k>=i;k--) a[j][k]-=a[i][k]*a[j][i];
	}
	for(int i=0;i<n;i++) printf("%.2lf\n",a[end[i]-root][size]);
}

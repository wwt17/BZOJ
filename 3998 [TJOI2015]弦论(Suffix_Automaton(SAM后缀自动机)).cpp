#include <cstdio>
typedef long long ll;
const int N=(int)5e5+5;

struct node{
	node *fa,*go[26];
	int len;
	ll val[2],all[2];
} mem[N*2],*newnode=mem;

node *root=newnode++;

node* extend(node *p,int c){
	node *np=newnode++;
	np->len=p->len+1;
	for(;p&&!p->go[c];p=p->fa) p->go[c]=np;
	if(!p)
		np->fa=root;
	else{
		node *q=p->go[c];
		if(q->len==p->len+1)
			np->fa=q;
		else{
			node *nq=newnode++;
			for(int x=0;x<26;x++) nq->go[x]=q->go[x];
			nq->fa=q->fa;
			nq->len=p->len+1;
			q->fa=np->fa=nq;
			for(;p&&p->go[c]==q;p=p->fa) p->go[c]=nq;
		}
	}
	return np;
}

int tot;
int sum[N];
node *seq[N*2];
int top;
char s[N],ans[N];

int main(){
	scanf("%s",s);
	node *tail=root;
	for(int i=0;s[i];i++){
		tail=extend(tail,s[i]-'a');
		tail->val[1]++;
	}
	tot=newnode-mem;
	for(int i=0;i<tot;i++) sum[mem[i].len]++;
	for(int i=1;s[i-1];i++) sum[i]+=sum[i-1];
	for(int i=0;i<tot;i++) seq[--sum[mem[i].len]]=mem+i;
	for(int i=tot-1;i>0;i--)
		seq[i]->fa->val[1]+=seq[i]->val[1],
		seq[i]->val[0]=1;
	for(int type=0;type<=1;type++)
		for(int i=tot-1;i>=0;i--){
			seq[i]->all[type]=seq[i]->val[type];
			for(int c=0;c<26;c++) if(seq[i]->go[c])
				seq[i]->all[type]+=seq[i]->go[c]->all[type];
		}
	root->all[1]-=root->val[1];
	root->val[1]=0;
	int type,k; scanf("%d%d",&type,&k);
	node *cur=root;
	if(k>cur->all[type]){
		puts("-1");
		return 0;
	}
	for(;;){
		if(k<=cur->val[type]) break;
		k-=cur->val[type];
		for(int c=0;c<26;c++) if(cur->go[c]){
			if(k<=cur->go[c]->all[type]){
				ans[top++]=c+'a';
				cur=cur->go[c];
				break;
			}
			k-=cur->go[c]->all[type];
		}
	}
	puts(ans);
}

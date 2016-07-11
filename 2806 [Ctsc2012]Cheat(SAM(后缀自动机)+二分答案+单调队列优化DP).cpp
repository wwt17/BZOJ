#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1100005;

int n,m;

struct node{
	node *fa,*go[3];
	int len;
} mem[N*4],*newnode=mem;

node *root=newnode++;

node *extend(node *p,int c){
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
			*nq=*q;
			nq->len=p->len+1;
			np->fa=q->fa=nq;
			for(;p&&p->go[c]==q;p=p->fa) p->go[c]=nq;
		}
	}
	return np;
}

char s[N];

int len[N];

int f[N],q[N];

inline int calc(int i){
	return f[i]-i;
}

int dp(int L){
	f[0]=0;
	int head=0,tail=0;
	for(int i=1;i<=m;i++){
		if(i-L>=0){
			while(head<tail&&calc(q[tail-1])<=calc(i-L)) tail--;
			q[tail++]=i-L;
		}
		while(head<tail&&q[head]<i-len[i]) head++;
		f[i]=f[i-1];
		if(head<tail) f[i]=max(f[i],calc(q[head])+i);
	}
	return f[m];
}

int main(){
	scanf("%d%d",&n,&m);
	node *tail=root;
	while(m--){
		scanf("%s",s);
		for(char *i=s;*i;i++) tail=extend(tail,*i-'0');
		tail=extend(tail,2);
	}
	while(n--){
		scanf("%s",s);
		node *cur=root;
		int i,now=0;
		for(i=0;s[i];){
			while(cur!=root&&!cur->go[s[i]-'0']) cur=cur->fa;
			now=min(now,cur->len);
			if(cur->go[s[i]-'0']) cur=cur->go[s[i]-'0'],++now;
			++i;
			len[i]=now;
		}
		m=i;
		int l=0,r=m+1;
		while(r-l>1){
			int mid=l+r>>1;
			if(dp(mid)*10>=m*9)
				l=mid;
			else
				r=mid;
		}
		printf("%d\n",l);
	}
}

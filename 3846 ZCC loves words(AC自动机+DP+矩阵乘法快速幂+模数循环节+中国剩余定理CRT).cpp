#include <cstdio>
typedef long long ll;
inline void inc(int &a,const int b,const int mo){
	if((a+=b)>=mo) a-=mo;
}
const int N=45;
long long L;
char s[N];
int m,n,len[N],ed[N],fail[N],next[N][26],prime[N],val[N];
int newnode(){
	++n;
	for(int c=0;c<26;c++) next[n][c]=0;
	fail[n]=0;
	return n;
}
int q[N];
void build(){
	int head=0,tail=0;
	fail[1]=1;
	q[tail++]=1;
	for(int c=0;c<26;c++)
		if(next[1][c])
			fail[next[1][c]]=1,
			q[tail++]=next[1][c];
		else
			next[1][c]=1;
	head++;
	while(head<tail){
		int u=q[head++];
		for(int c=0;c<26;c++)
			if(next[u][c]){
				fail[next[u][c]]=next[fail[u]][c];
				q[tail++]=next[u][c];
			}
			else
				next[u][c]=next[fail[u]][c];
	}
}
void exgcd(ll a,ll &x,ll b,ll &y,ll c){
	if(!b){
		x=c/a;
		y=0;
		return;
	}
	exgcd(b,y,a%b,x,c);
	y-=a/b*x;
}
struct data{
	int val,mo;
	data(int val=0,int mo=1):val(val),mo(mo){
	}
	friend data merge(const data &f1,const data &f2){
		ll k1,k2;
		exgcd(f1.mo,k1,f2.mo,k2,f2.val-f1.val);
		if((k1%=f2.mo)<0) k1+=f2.mo;
		return data(k1*f1.mo+f1.val,f1.mo*f2.mo);
	}
};
int opt[N][N],ans[N][N],tmp[N][N];
void mul(int c[N][N],int a[N][N],int b[N][N],int mo){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			tmp[i][j]=0;
			for(int k=1;k<=n;k++)
				inc(tmp[i][j],a[i][k]*b[k][j]%mo,mo);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=tmp[i][j];
}
int f[200][N];
void dp(int l,int mo){
	for(int i=1;i<=l;i++){
		for(int j=1;j<=n;j++) val[j]=1;
		for(int j=1;j<=m;j++) (val[ed[j]]*=(i+len[j])*prime[j]%mo)%=mo;
		for(int j=0;j<n;j++) (val[q[j]]*=val[fail[q[j]]])%=mo;
		for(int j=1;j<=n;j++) f[i][j]=0;
		for(int j=1;j<=n;j++)
			for(int c=0;c<26;c++)
				inc(f[i][next[j][c]],f[i-1][j],mo);
		for(int j=1;j<=n;j++)
			f[i][j]=f[i][j]*val[j]%mo;
	}
}
data work(int mo){
	for(int left=1;left<=n;left++){
		for(int j=1;j<=n;j++) f[0][j]=0;
		f[0][left]=1;
		dp(mo,mo);
		for(int right=1;right<=n;right++)
			opt[left][right]=f[mo][right];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans[i][j]=0;
	ans[1][1]=1;
	for(long long x=L/mo;x;x>>=1,mul(opt,opt,opt,mo))
		if(x&1) mul(ans,ans,opt,mo);
	int len=L%mo;
	for(int left=1;left<=n;left++) f[0][left]=ans[1][left];
	dp(len,mo);
	int ans=0;
	for(int right=1;right<=n;right++) inc(ans,f[len][right],mo);
	return data(ans,mo);
}
int main(){
	for(int Case=1;scanf("%d%lld",&m,&L)!=EOF;Case++){
		n=0;
		newnode();
		for(int i=2,cnt=0;cnt<m;i++){
			bool ok=true;
			for(int j=2;j<i;j++) if(i%j==0){
				ok=false;
				break;
			}
			if(ok) prime[++cnt]=i;
		}
		for(int i=1;i<=m;i++){
			scanf("%s",s);
			int cur=1;
			char *c;
			for(c=s;*c;c++){
				*c-='A';
				if(!next[cur][*c]) next[cur][*c]=newnode();
				cur=next[cur][*c];
			}
			len[i]=c-s;
			ed[i]=cur;
		}
		build();
		data ans;
		ans=merge(ans,work(179));
		ans=merge(ans,work(173));
		ans=merge(ans,work(163));
		printf("Case #%d: %d\n",Case,ans.val);
	}
}

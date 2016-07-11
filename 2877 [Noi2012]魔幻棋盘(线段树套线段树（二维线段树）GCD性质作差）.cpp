#include <cstdio>
#include <vector>
typedef long long ll;
const int N=500005,logN=22;
int n,m,x,y,X2,X,x1,x2,y1,y2;
ll gcd(const ll a,const ll b){
	return b?gcd(b,a%b):a;
}
std::vector<ll> val[N];
ll D,vxy,a[N*4],b[N*4],*s[N*4],t[N*4*4];
void modify(ll *a,int cur,int beg,int end){
	if(end-beg==1){
		a[cur]+=D;
		return;
	}
	int mid=beg+end>>1;
	if(X<=mid)
		modify(a,cur<<1  ,beg,mid);
	else
		modify(a,cur<<1|1,mid,end);
	a[cur]=gcd(a[cur<<1],a[cur<<1|1]);
}
void query(ll *a,int cur,int beg,int end){
	if(y2<=beg||y1>=end) return;
	if(y1<=beg&&y2>=end){
		D=gcd(D,a[cur]);
		return;
	}
	int mid=beg+end>>1;
	query(a,cur<<1  ,beg,mid);
	query(a,cur<<1|1,mid,end);
}
void update2(int Cur,int cur,int beg,int end){
	if(end-beg>1){
		int mid=beg+end>>1;
		if(X<=mid)
			update2(Cur,cur<<1  ,beg,mid);
		else
			update2(Cur,cur<<1|1,mid,end);
	}
	s[Cur][cur]=gcd(s[Cur<<1][cur],s[Cur<<1|1][cur]);
}
void modify2(int cur,int beg,int end){
	if(end-beg==1){
		modify(s[cur],1,0,m);
		return;
	}
	int mid=beg+end>>1;
	if(X2<=mid)
		modify2(cur<<1,beg,mid);
	else
		modify2(cur<<1|1,mid,end);
	update2(cur,1,0,m);
}
void query2(int cur,int beg,int end){
	if(x2<=beg||x1>=end) return;
	if(x1<=beg&&x2>=end) return query(s[cur],1,0,m);
	int mid=beg+end>>1;
	query2(cur<<1  ,beg,mid);
	query2(cur<<1|1,mid,end);
}
void add(int x,int y){
	if(x>n||y>m) return;
	X2=x;
	X=y;
	modify2(1,0,n);
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	int T; scanf("%d",&T);
	for(int j=0;j<=m;j++) val[0].push_back(0);
	for(int i=1;i<=n;i++){
		val[i].push_back(0);
		for(int j=1;j<=m;j++){
			scanf("%lld",&D);
			val[i].push_back(D);
		}
	}
	vxy=val[x][y];
	for(int i=1;i<=n;i++){
		X=i;
		D=val[i][y]-val[i-1][y];
		modify(a,1,0,n);
	}
	for(int j=1;j<=m;j++){
		X=j;
		D=val[x][j]-val[x][j-1];
		modify(b,1,0,m);
	}
	for(int i=1;i<=n*4;i++) s[i]=t+(i-1)*m*4;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			X2=i;
			X=j;
			D=val[i][j]-val[i-1][j]-val[i][j-1]+val[i-1][j-1];
			modify2(1,0,n);
		}
	while(T--){
		int type; scanf("%d%d%d%d%d",&type,&x1,&y1,&x2,&y2);
		if(type==0){
			x1=x-x1;
			x2=x+x2;
			y1=y-y1;
			y2=y+y2;
			D=vxy;
			query2(1,0,n);
			query(b,1,0,m);
			y1=x1;
			y2=x2;
			query(a,1,0,n);
			printf("%lld\n",D<0?-D:D);
		}
		else{
			x2++;
			y2++;
			scanf("%lld",&D);
			if(x>=x1&&x<x2&&y>=y1&&y<y2) vxy+=D;
			if(y>=y1&&y<y2){
				if(x1<=n) X=x1,modify(a,1,0,n);
				D*=-1;
				if(x2<=n) X=x2,modify(a,1,0,n);
				D*=-1;
			}
			if(x>=x1&&x<x2){
				if(y1<=m) X=y1,modify(b,1,0,m);
				D*=-1;
				if(y2<=m) X=y2,modify(b,1,0,m);
				D*=-1;
			}
			add(x1,y1);
			add(x2,y2);
			D*=-1;
			add(x1,y2);
			add(x2,y1);
			D*=-1;
		}
	}
}

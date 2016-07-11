#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const int N=10005,mo=(int)1e9+9;

const ll inv[7]={0,1,500000005,666666673,750000007,200000002,833333341};

int r,c,n;

ll ans;

vector<char> a[N];
vector<int> las[N],nex[N],up[N],down[N];

int s[3],t[N][3];

void inc(int &a,const int b){
	a+=b;
	if(a>=mo) a-=mo;
	if(a<0) a+=mo;
}

void add(int x,int d){
	s[0]=d;
	for(int i=1;i<3;i++) s[i]=1LL*s[i-1]*x%mo;
	for(;x<=n;x+=x&-x)
		for(int i=0;i<3;i++)
			inc(t[x][i],s[i]);
}
void query(int x){
	for(int i=0;i<3;i++) s[i]=0;
	for(;x;x-=x&-x)
		for(int i=0;i<3;i++)
			inc(s[i],t[x][i]);
}

int main(){
	scanf("%d%d%d",&r,&c,&n);
	for(int i=0;i<=r+1;i++){
		a[i].resize(c+2);
		las[i].resize(c+2);
		nex[i].resize(c+2);
		up[i].resize(c+2);
		down[i].resize(c+2);
	}
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			a[i][j]=1;
	while(n--){
		int x,y; scanf("%d%d",&x,&y);
		a[x][y]=0;
	}
	n=(c+1)/2;
	for(int i=0;i<=r+1;i++){
		las[i][0]=0;
		for(int j=1;j<=c;j++)
			las[i][j]=a[i][j]?las[i][j-1]:j;
		nex[i][c+1]=c+1;
		for(int j=c;j>=1;j--)
			nex[i][j]=a[i][j]?nex[i][j+1]:j;
	}
	for(int j=0;j<=c+1;j++){
		up[0][j]=0;
		for(int i=1;i<=r;i++)
			up[i][j]=a[i][j]?up[i-1][j]:i;
		down[r+1][j]=r+1;
		for(int i=r;i>=1;i--)
			down[i][j]=a[i][j]?down[i+1][j]:i;
	}
	for(int j=1;j<=c;j++){
		for(int i=1;i<=r+1;i++){
			if(a[i][j]==1){
				int rad=min(j-las[i][j],nex[i][j]-j)-1;
				if(rad>=1){
					query(rad-1);
					ll c=rad;
					(ans+=(c*(c+1)%mo*inv[2]%mo*s[0]%mo
					    -(2*c+1)*inv[2]%mo*s[1]%mo
					    +inv[2]*s[2]%mo
					    )%mo*(down[i][j]-i-1)
					)%=mo;
				}
				rad=min(j-las[i-1][j],nex[i-1][j]-j)-1;
				if(rad>=1){
					add(1,i-1-up[i-1][j]-1);
					add(rad+1,-(i-1-up[i-1][j]-1));
				}
			}
			else{
				for(i=up[i-1][j]+1;a[i][j]==1;i++){
					int rad=min(j-las[i-1][j],nex[i-1][j]-j)-1;
					if(rad>=1){
						add(1,-(i-1-up[i-1][j]-1));
						add(rad+1,i-1-up[i-1][j]-1);
					}
				}
			}
		}
	}
	printf("%d\n",int((ans%mo+mo)%mo));
}

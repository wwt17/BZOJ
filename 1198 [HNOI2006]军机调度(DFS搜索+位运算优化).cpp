#include <cstdio>
const int N=12,M=17,D=31;
int n,m,j,now,ans;
int can[N],working[N];
bool flag[N][D];
struct task{
	int st,en,p,r;
} b[M];
void search1();
void search2(int i,int cnt){
	if(cnt==b[j].p){
		j++;
		search1();
		j--;
		return;
	}
	if(i==n) return;
	search2(i+1,cnt);
	if(can[i]>>j&1&&!(working[i]&(1<<b[j].en)-(1<<b[j].st))){
		working[i]^=(1<<b[j].en)-(1<<b[j].st);
		search2(i+1,cnt+1);
		working[i]^=(1<<b[j].en)-(1<<b[j].st);
	}
}
void search1(){
	if(j==m){
		if(now>ans) ans=now;
		return;
	}
	j++;
	search1();
	j--;
	now+=b[j].r;
	search2(0,0);
	now-=b[j].r;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		int k; scanf("%d",&k);
		while(k--){
			int j; scanf("%d",&j); j--;
			can[i]|=1<<j;
		}
	}
	for(j=0;j<m;j++){
		scanf("%d%d%d%d",&b[j].st,&b[j].en,&b[j].p,&b[j].r);
		b[j].st--;
	}
	j=0;
	search1();
	printf("%d\n",ans);
}

#include <cstdio>
#include <map>
using namespace std;
const int Len=1005;
int n,len,mo,t,c,l,r,d,sum[2][Len*2][Len*4];
typedef pair<int,int> pii;
map<int,pii> s;
void add(int x,int y,int d){
	for(int i=x+1;i<=mo;i+=i&-i)
		for(int j=y+x+1;j<=mo*2;j+=j&-j)
			sum[0][i][j]+=d;
	for(int i=x+1;i<=mo;i+=i&-i)
		for(int j=y+(mo-1-x)+1;j<=mo*2;j+=j&-j)
			sum[1][i][j]+=d;
}
int qsum(int d,int x,int y){
	if(x<=0||y<=0) return 0;
	int s=0;
	for(int i=x;i;i-=i&-i)
		for(int j=y;j;j-=j&-j)
			s+=sum[d][i][j];
	return s;
}
int query(int d,int x0,int x1,int l,int r){
	if(x0<0 ) return query(d,x0+mo,mo,l-mo,r-mo)+query(d,0,x1,l,r);
	if(x1>mo) return query(d,x0,mo,l,r)+query(d,0,x1-mo,l-mo,r-mo);
	return qsum(d,x0,l)-qsum(d,x1,l)-qsum(d,x0,r)+qsum(d,x1,r);
}
int main(){
	scanf("%d%d",&n,&len);
	mo=len*2;
	while(n--){
		int type; scanf("%d%d",&type,&t);
		if(type==1){
			scanf("%d%d%d%d",&c,&l,&r,&d);
			t-=l*d;
			t=(t%mo+mo)%mo;
			r-=l;
			s[c]=pii(t,r);
			add(t,r,1);
		}
		else
		if(type==2){
			scanf("%d%d",&l,&r);
			t%=mo;
			l--;
			int ans=
				 query(0,t-1+1,t+(r<len?r:r-1)+1,l+t+1,len+r+t+1)
				+query(1,t-r-1+1,t-1+1,l+(mo-1-t)+1,len+r+(mo-1-t)+1);
			printf("%d\n",ans);
		}
		else
		if(type==3){
			scanf("%d",&c);
			add(s[c].first,s[c].second,-1);
			s.erase(c);
		}
	}
}

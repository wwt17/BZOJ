#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef double db;

const int N=4e5+5,logN=19,Mem=15648000,inf=1e8+5;
const db eps=1e-7;
int n,m,l,r;
char s;

struct vec{
	int x,y;
	vec(int _x=0,int _y=0):x(_x),y(_y){
	}
} pool[Mem],*newvec=pool;

vec now,*a[N][logN][3],tmp[N];
#define len(x,y) (a[x][y][2]-a[x][y][0])
int b[N];

inline ll dot(vec &a,vec &b){
	return (ll)a.x*b.x+(ll)a.y*b.y;
}
inline ll dot(vec &a,vec &b,vec &c){
	return ll(b.x-a.x)*(c.x-b.x)+ll(b.y-a.y)*(c.y-b.y);
}
inline ll cross(vec &a,vec &b,vec &c){
	return ll(b.x-a.x)*(c.y-a.y)-ll(c.x-a.x)*(b.y-a.y);
}

inline bool cmp(const vec a,const vec b){
	return a.x<b.x||a.x==b.x&&a.y<b.y;
}

vec* query(vec *l,vec *r){
	vec *ans=l;
	
	while(r-l>1){
		vec *mid=l+(r-l>>1);
		if(dot(mid[0],now)<dot(mid[1],now))
			l=mid;
		else
			r=mid;
	}
	if(dot(*r,now)>dot(*ans,now)) ans=r;
	return ans;
}

void add(){
	++n;
	a[n][0][0]=newvec;
	newvec[0]=newvec[1]=now;
	a[n][0][1]=newvec+1;
	a[n][0][2]=newvec+1;
	newvec+=2;
	for(int i=1;(1<<i)<=(n&-n);i++){
		b[n]=i;
		int l=0;
		memcpy(tmp,a[n-(1<<i-1)][i-1][0],sizeof(vec)*len(n-(1<<i-1),i-1));
		l+=len(n-(1<<i-1),i-1);
		memcpy(tmp+l,a[n][i-1][0],sizeof(vec)*len(n,i-1));
		l+=len(n,i-1);
		sort(tmp,tmp+l,cmp);
		vec *top=newvec;
		a[n][i][0]=newvec;
		for(int j=0;j<l;j++){
			while(top-newvec>1&&(
				  cross(top[-2],top[-1],tmp[j])<0
				||cross(top[-2],top[-1],tmp[j])==0&&dot(top[-2],top[-1],tmp[j])>=0
				)) top--;
			*top++=tmp[j];
		}
		a[n][i][1]=newvec=top;
		for(int j=l-1;j>=0;j--){
			while(top-newvec>1&&(
				  cross(top[-2],top[-1],tmp[j])<0
				||cross(top[-2],top[-1],tmp[j])==0&&dot(top[-2],top[-1],tmp[j])>=0
				)) top--;
			*top++=tmp[j];
		}
		a[n][i][2]=top-1;
		newvec=top;
	}
}

ll query(){
	l--;
	ll ans=-2LL*inf*inf;
	for(int x=l,xx;x;x=xx){
		xx=x+(x&-x);
		if(xx>r) break;
		ans=max(ans,dot(*(now.y<0?query(a[xx][b[x]][0],a[xx][b[x]][1]):query(a[xx][b[x]][1],a[xx][b[x]][2])),now));
	}
	for(int x=r,xx;x;x=xx){
		xx=x-(x&-x);
		if(xx<l) break;
		ans=max(ans,dot(*(now.y<0?query(a[x][b[x]][0],a[x][b[x]][1]):query(a[x][b[x]][1],a[x][b[x]][2])),now));
	}
	return ans;
}

int main(){
	scanf("%d %c",&m,&s);
	ll lastans=0;
	while(m--) switch(getchar()){
		case 'A':
			scanf("%d%d",&now.x,&now.y);
			if(s!='E'){
				now.x^=lastans;
				now.y^=lastans;
			}
			add();
			break;
		case 'Q':
			scanf("%d%d%d%d",&now.x,&now.y,&l,&r);
			if(s!='E'){
				now.x^=lastans;
				now.y^=lastans;
				l^=lastans;
				r^=lastans;
			}
			printf("%lld\n",lastans=query());
			lastans&=0x7fffffff;
			break;
		default:
			m++;
	}
}

#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100;
typedef pair<short,short> range;
int l,r;
struct data{
	short cnt,len;
} T[2000*4+5];
void add(int i,int L,int R){
	if(l<=L&&R<=r) T[i].cnt++;
	else{
		if(l<(L+R)>>1) add(i<<1,L,(L+R)>>1);
		if(r>(L+R)>>1) add(i<<1|1,(L+R)>>1,R);
	}
	T[i].len=T[i].cnt?R-L:T[i<<1].len+T[i<<1|1].len;
}
void del(int i,int L,int R){
	if(l<=L&&R<=r) T[i].cnt--;
	else{
		if(l<(L+R)>>1) del(i<<1,L,(L+R)>>1);
		if(r>(L+R)>>1) del(i<<1|1,(L+R)>>1,R);
	}
	T[i].len=T[i].cnt?R-L:T[i<<1].len+T[i<<1|1].len;
}
struct cube{
	range x,y,z; bool exist;
	inline void read(){
		short X,Y,Z,R;
		scanf("%hd%hd%hd%hd",&X,&Y,&Z,&R);
		x=range(X-R,X+R);
		y=range(Y-R,Y+R);
		z=range(Z-R,Z+R);
	}
} C[N];
int n; short Y,Z;
short *tx[N<<1],*ty[N<<1];
inline bool cmp(const short* a,const short* b){
	return *a < *b;
}
long long queryrec(){
	long long Ans=0;
	for(int i=0;i<n<<1;i++){
		if(i) Ans+=(*ty[i]-*ty[i-1])*T[1].len;
		if((ty[i]-&C[0].y.first)%7==0){
			cube* cur=(cube*)(ty[i]-2);
			if(cur->exist){
				l=cur->z.first;
				r=cur->z.second;
				add(1,-1000,1000);
			}
		}
		else{
			cube* cur=(cube*)(ty[i]-3);
			if(cur->exist){
				l=cur->z.first;
				r=cur->z.second;
				del(1,-1000,1000);
			}
		}
	}
	return Ans;
}
int main(){
	scanf("%u",&n);
	for(int i=0;i<n;i++) C[i].read();
	for(int i=0;i<n;i++) tx[i<<1]=&C[i].x.first,tx[i<<1|1]=&C[i].x.second;
	sort(tx,tx+(n<<1),cmp);
	for(int i=0;i<n;i++) ty[i<<1]=&C[i].y.first,ty[i<<1|1]=&C[i].y.second;
	sort(ty,ty+(n<<1),cmp);
	long long Ans=0;
	for(int i=0;i<n<<1;i++){
		if(i) Ans+=(*tx[i]-*tx[i-1])*queryrec();
		if((tx[i]-&C[0].x.first)%7==0)
			((cube*)tx[i])->exist=true;
		else
			((cube*)(tx[i]-1))->exist=false;
	}
	printf("%llu\n",Ans);
}

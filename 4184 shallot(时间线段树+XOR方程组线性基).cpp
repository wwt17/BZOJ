#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

const int N=500005,logN=20,B=31;

int n,m;

struct data{
	int val;
	int l,r;
	friend bool operator < (const data &a,const data &b){
		return a.val<b.val;
	}
} a[N];

multiset<data> s;

int base[logN][B];
int len[logN];
data *b[logN][N];

bool add(int base[B],int x){
	for(int i=B-1;i>=0;i--) if(x>>i&1){
		if(base[i]) x^=base[i];
		else{
			base[i]=x;
			return true;
		}
	}
	return false;
}

int calc(int base[B]){
	int ans=0;
	for(int i=B-1;i>=0;i--) if((ans^base[i])>ans) ans^=base[i];
	return ans;
}

inline void cp(int x,int y){
	for(int i=0;i<B;i++) base[x][i]=base[y][i];
	len[x]=len[y];
	for(int i=0;i<len[x];i++) b[x][i]=b[y][i];
}

void work(int lev,int beg,int end){
	int j=0;
	for(int i=0;i<len[lev];i++)
		if(b[lev][i]->r<=beg||b[lev][i]->l>=end); else
		if(b[lev][i]->l<=beg&&b[lev][i]->r>=end)
			add(base[lev],b[lev][i]->val);
		else
			b[lev][j++]=b[lev][i];
	len[lev]=j;
	if(end-beg==1){
		printf("%d\n",calc(base[lev]));
		return;
	}
	int mid=beg+end>>1;
	cp(lev+1,lev);
	work(lev+1,beg,mid);
	cp(lev+1,lev);
	work(lev+1,mid,end);
}

int main(){
	scanf("%d",&m);
	for(int tim=0;tim<m;tim++){
		int x; scanf("%d",&x);
		if(x>0){
			s.insert((data){x,tim,0});
		}
		else{
			multiset<data>::iterator loc=s.find((data){-x,0,tim});
			a[n]=*loc;
			a[n].r=tim;
			n++;
			s.erase(loc);
		}
	}
	while(!s.empty()){
		a[n]=*s.begin();
		a[n].r=m;
		n++;
		s.erase(s.begin());
	}
	len[0]=n;
	for(int i=0;i<n;i++) b[0][i]=a+i;
	work(0,0,m);
}

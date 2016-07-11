#include <cstdio>
#include <cstdlib>
#include <set>
#include <queue>
using namespace std;
#define INF 0x7FFFFFFF
template<class T>
inline bool mini(T &a,const T b){
	return b<a?(a=b,true):false;
}
#define size 500050
int N,M,i,k,a[size],b[size],num[size];
struct qset{
	multiset<int> s;
	int Min;
	qset():Min(INF){}
	inline void insert(int x){
		set<int>::iterator i=s.insert(x),j=i;
		if(i!=s.begin()) mini(Min,x-*--i);
		if(++j!=s.end()) mini(Min,*j-x);
	}
} All;
struct state{
	bool in; int val,i,x;
	state(bool _in,int _val,int _i=0,int _x=0):
		in(_in),val(_val),i(_i),x(_x){}
	inline bool legal()const{
		return in||x==num[i];
	}
	bool operator<(const state &b)const{
		return val>b.val;
	}
};
priority_queue<state> q;
int main(){
	scanf("%u%u",&N,&M);
	for(i=1;i<=N;i++){
		scanf("%u",&a[i]);
		All.insert(b[i]=a[i]);
	}
	for(i=1;i<N;i++) q.push(state(false,abs(b[i]-a[i+1]),i,num[i]=1));
	char opt[14];
	while(M--)
		switch(getchar(),getchar(),getchar(),getchar(),getchar(),getchar()){
			case 'R'://INSERT
				scanf("T%u%u",&i,&k);
				All.insert(k);
				q.push(state(true,abs(k-b[i])));
				b[i]=k;
				if(i<N) q.push(state(false,abs(b[i]-a[i+1]),i,++num[i]));
				break;
			case 'G'://MIN_GAP
				scanf("AP");
				while(!q.top().legal()) q.pop();
				printf("%d\n",q.top().val);
				break;
			case 'S'://MIN_SORT_GAP
				scanf("ORT_GAP");
				printf("%d\n",All.Min);
				break;
		}
}

/*
可以模拟退火，2^n枚举第3类的方案，先按某个值排序，随机交换两个位置
原创确定性算法：同样2^n枚举第3类的方案，有如下性质：1.A机器的安排一定是所有第1类在前、第2类在后，B机器同样；2.第1类的在两机器中的相对位置相同，第2类同样。这样就可以二分答案，对于每一类，前面的挤在最前面，后面的挤在最后面，记录当前放完的位置的两个指针的差dis。合法方案必须满足a<=dis（不重叠）。然后贪心地放使得dis减小最大的合法方案。 
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=22;
int n,lim;
bool ok;
struct task{
	int t,a,b;
} tas[N];
bool cmpt(const task &a,const task &b){
	return a.t<b.t;
}
bool cmpa(const task &a,const task &b){
	return a.a<b.a;
}
bool cmpb(const task &a,const task &b){
	return a.b<b.b;
}
int sum[3][3];
#define calc1(i) (tas[i].b-tas[i].a)
#define calc2(i) (tas[i].a-tas[i].b)
struct cmp{
	bool operator () (const int i,const int j){
		return tas[i].b-tas[i].a<tas[j].b-tas[j].a;
	}
};
bool flag[N];
bool work(){
	for(int i=0;i<n;i++) flag[i]=false;
	if(sum[1][1]+sum[1][2]>lim){
		int dis=lim-sum[1][2];
		int Cnt=0;
		for(int i=0;i<n;i++) if(tas[i].t==1) Cnt++;
		while(Cnt--){
			int k=-1;
			for(int i=0;i<n;i++) if(tas[i].t==1&&!flag[i]&&tas[i].a<=dis)
				if(k==-1||calc1(i)>calc1(k))
					k=i;
			if(k==-1) return false;
			flag[k]=true;
			dis+=calc1(k);
		}
		return true;
	}
	else{
		int dis=lim-sum[2][1];
		int Cnt=0;
		for(int i=0;i<n;i++) if(tas[i].t==2) Cnt++;
		while(Cnt--){
			int k=-1;
			for(int i=0;i<n;i++) if(tas[i].t==2&&!flag[i]&&tas[i].b<=dis)
				if(k==-1||calc2(i)>calc2(k))
					k=i;
			if(k==-1) return false;
			flag[k]=true;
			dis+=calc2(k);
		}
		return true;
	}
}
void dfs(int i){
	if(i==n){
		ok=work();
		return;
	}
	if(tas[i].t!=3){
		sum[tas[i].t][1]+=tas[i].a;
		sum[tas[i].t][2]+=tas[i].b;
		dfs(i+1);
		sum[tas[i].t][1]-=tas[i].a;
		sum[tas[i].t][2]-=tas[i].b;
		return;
	}
	tas[i].t=1;
	sum[tas[i].t][1]+=tas[i].a;
	sum[tas[i].t][2]+=tas[i].b;
	dfs(i+1);
	sum[tas[i].t][1]-=tas[i].a;
	sum[tas[i].t][2]-=tas[i].b;
	if(ok){
		tas[i].t=3;
		return;
	}
	tas[i].t=2;
	sum[tas[i].t][1]+=tas[i].a;
	sum[tas[i].t][2]+=tas[i].b;
	dfs(i+1);
	sum[tas[i].t][1]-=tas[i].a;
	sum[tas[i].t][2]-=tas[i].b;
	tas[i].t=3;
}
int main(){
	scanf("%d",&n);
	int sa=0,sb=0;
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&tas[i].t,&tas[i].a,&tas[i].b);
		sa+=tas[i].a;
		sb+=tas[i].b;
	}
	sort(tas,tas+n,cmpt);
	int l=max(sa,sb)-1,r=sa+sb;
	while(r-l>1){
		lim=(l+r)/2;
		ok=false;
		dfs(0);
		if(ok)
			r=lim;
		else
			l=lim;
	}
	printf("%d\n",r);
}

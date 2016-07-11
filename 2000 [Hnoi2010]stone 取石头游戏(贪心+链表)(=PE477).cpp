/*
可以被分为两个栈和若干个双端队列 
贪心：
1. 对于栈底的2个元素，如果栈底上面的元素大于栈底元素，那么谁取上面的那个元素谁吃亏。所以大家都不愿意取。所以一定是到最后不得不取才取的。可以由总共元素个数的奇偶性累计进答案。
2. 对于栈或队列中的连续3个元素a[i-1],a[i],a[i+1],如果a[i-1]<=a[i]>=a[i+1]，那么可以把3个元素删去，代之以一个a[i-1]+a[i+1]-a[i]。因为不管从什么方向取都是这个结果。
3. 对于剩余的元素，栈一定满足从栈顶到栈底递减，队列一定满足从两边到中间递减。这样，最大的元素一定可以取。排序后贪心取最大的即可。 
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1000005;
int n,cnt,last[N],next[N];
bool bo[N];
long long sum,ans,a[N];
int ord[N];
void remove(int u){
	bo[u]=false;
	next[last[u]]=next[u];
	last[next[u]]=last[u];
}
void check(int i){
	while(bo[last[i]]&&bo[i]&&bo[next[i]]&&a[last[i]]<=a[i]&&a[i]>=a[next[i]]){
		a[i]=a[last[i]]+a[next[i]]-a[i];
		remove(last[i]);
		remove(next[i]);
		check(last[i]);
	}
}
bool cmp(const int i,const int j){
	return a[i]>a[j];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),cnt+=bo[i]=a[i],sum+=a[i];
	for(int i=1;i<=n;i++) last[i]=i-1,next[i]=i+1;
	next[0]=1;
	last[1]=0;
	next[n]=0;
	last[0]=n;
	for(int i=next[0];i;i=next[i])
		check(i);
	while(bo[next[0]]&&bo[next[next[0]]]&&a[next[0]]>=a[next[next[0]]]){
		ans+=cnt&1?a[next[0]]-a[next[next[0]]]:a[next[next[0]]]-a[next[0]];
		remove(next[0]);
		remove(next[0]);
	}
	while(bo[last[0]]&&bo[last[last[0]]]&&a[last[0]]>=a[last[last[0]]]){
		ans+=cnt&1?a[last[0]]-a[last[last[0]]]:a[last[last[0]]]-a[last[0]];
		remove(last[0]);
		remove(last[0]);
	}
	n=0;
	for(int i=next[0];i;i=next[i]) if(bo[i]) ord[n++]=i;
	sort(ord,ord+n,cmp);
	for(int i=0;i<n;i++) if(i&1) ans-=a[ord[i]]; else ans+=a[ord[i]];
	printf("%lld %lld\n",(sum+ans)/2,(sum-ans)/2);
}

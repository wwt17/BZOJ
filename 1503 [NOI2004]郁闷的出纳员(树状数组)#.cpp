#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define size 200005
#define Base 100001
#define maxn (1<<18)
int a[size],s[size],n,Min,k,sum=0,base=Base,leave=0;
inline void ins(int x,int k) {
	while (x<size) s[x]-=k,x+=x&-x;
}
inline int find(int k) {
	if (k<=0) return -1;
	int ret=0,cnt=0,tmp,sum;
	for (int r=maxn>>1;r;r>>=1)
		if ((tmp=ret+r)<size&&(sum=cnt+s[tmp])<k)
			ret=tmp,cnt=sum;
	return ret+1-base;
}
int main() {
	//scanf("%d%d\n",&n,&Min);
	cin>>n>>Min;
	char order;
	while (n--) {
		//scanf("%c%d\n",&order,&k);
		cin>>order>>k;
		switch (order) {
			case 'I':
				if (k>=Min) {
					++a[base+k];
					++sum;
					ins(base+k,1);
				}
				break;
			case 'A':
				base-=k;
				break;
			case 'S':
				for (;k;++base,--k)
					if (a[base+Min]) {
						leave+=a[base+Min];
						sum-=a[base+Min];
						ins(base+Min,-a[base+Min]);
						a[base+Min]=0;
					}
				break;
			case 'F':
				printf("%d\n",find(sum-k+1));
		}
	}
	printf("%d\n",leave);
	system("pause");
}

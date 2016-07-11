#include <cstdio>

const int N=250005;
int n,k,best[15],d[N],t[N],*t1,*t2,base1,base2;

inline int max(const int a,const int b){
	return a>b?a:b;
}

void update(int *t,int n,int x,int d){
	for(;x<=n;x+=x&-x)
		if(d>t[x]) t[x]=d;
}
int query(int *t,int x){
	int ans=0;
	for(;x;x-=x&-x)
		if(t[x]>ans) ans=t[x];
	return ans;
}
int find(int *t,int n,int base,int d){
	int x=0,now=0;
	for(;base;base>>=1)
		if(x+base<=n&&max(now,t[x+base])<d)
			now=max(now,t[x+=base]);
	return x;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",d+i);
		int j=10;
		while(j&&d[i]>d[best[j]]){
			best[j+1]=best[j];
			j--;
		}
		best[j+1]=i;
	}
	t1=t;
	t2=t+k;
	for(base1=1;base1<=k-1;base1<<=1);
	for(base2=1;base2<=n-k;base2<<=1);
	for(int i=1;i<k;i++) update(t1,k-1,k-i,d[i]);
	for(int i=k+1;i<=n;i++) update(t2,n-k,i-k,d[i]);
	int q; scanf("%d",&q);
	int i,j,e,b;
	while(q--)
		switch(getchar()){
			case 'E':
				scanf("%d%d",&i,&e);
				j=10;
				for(;j&&best[j]!=i;j--);
				if(!j) j=10;
				for(;j>e;j--) best[j]=best[j-1];
				d[i]=d[best[e]];
				best[e]=i;
				for(;j;j--){
					++d[best[j]];
					if(best[j]<k)
						update(t1,k-1,k-best[j],d[best[j]]);
					else
					if(best[j]>k)
						update(t2,n-k,best[j]-k,d[best[j]]);
				}
				break;
			case 'F':
				scanf("%d",&b);
				if(b<k)
					printf("%d\n",k-b+find(t2,n-k,base2,query(t1,k-b)));
				else
				if(b>k)
					printf("%d\n",b-k+find(t1,k-1,base1,query(t2,b-k)));
				else
					puts("0");
				break;
			default: q++;
		}
}

#include <cstdio>
const int P=10007;
const int N=50001;
int n,m,sum[N],f[N];
int main(){
	scanf("%u%u",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",sum+i),sum[i]+=sum[i-1];
	int l=0,r=50000000,mid;
	while(l+1<r){
		mid=(l+r)>>1;
		int i,j=0,k=m+1;
		for(i=1;i<=n;i++)
			if(sum[i]-sum[j]>mid){
				j=--i;
				if(!--k) goto out;
			}
		out:
		(k?r:l)=mid;
	}
	printf("%u",r);
	int ans=0;
	f[0]=1;
	for(int k=0;k<=m;k++){
		int j=n,tmp=f[n];
		for(int i=n;i>k;i--){
			tmp-=f[i];
			while(j>k&&sum[i]-sum[j-1]<=r)
				tmp+=f[--j];
			f[i]=tmp%P;
		}
		ans=(ans+f[n])%P;
	}
	printf(" %u\n",ans);
}

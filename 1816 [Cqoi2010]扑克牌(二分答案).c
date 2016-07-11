int n,i,a[51],l,r,mid,ans; long long s;
int main(){
	scanf("%u",&n);
	for(i=0;i<=n;i++) scanf("%u",a+i);
	l=0,r=1000000000;
	while(l<=r){
		mid=(l+r)>>1;
		for(s=i=0;i<=n&&(s+=a[i]<mid?mid-a[i]:0)<=mid;i++);
		i<=n?(r=mid-1):(ans=mid,l=mid+1);
	}
	printf("%u\n",ans);
}

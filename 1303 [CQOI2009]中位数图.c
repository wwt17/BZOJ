int n,b,i,k,s,a[100000],
memsum[2][200000],
*suml=memsum[0]+99999,
*sumr=memsum[1]+99999;
int main(){
	scanf("%u%u",&n,&b);
	for(i=0;i<n;i++){
		scanf("%u",a+i);
		if(a[i]==b) k=i;
	}
	a[k]=0;
	for(suml[s=0]++,i=k-1;i>=0;i--)
		suml[a[i]<b?++s:--s]++;
	for(sumr[s=0]++,i=k+1;i< n;i++)
		sumr[a[i]>b?++s:--s]++;
	int Ans=0;
	for(s=-n+1;s<n;s++)
		Ans+=suml[s]*sumr[s];
	printf("%u\n",Ans);
}

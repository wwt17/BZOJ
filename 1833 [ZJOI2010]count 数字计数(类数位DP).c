long long a,b,sum,suml,sumr,cnt[10],tot; int i,level;
int main(){
	scanf("%llu%llu",&a,&b);
	for(a--,b++,sum=1;a||b;a/=10,b/=10,sum*=10,level++){
		i=a%10; if(a) cnt[i]+=suml;
		while(i++<9) cnt[i]+=sum,tot+=sum/10*level,suml+=sum;
		i=b%10;       cnt[i]+=sumr;
		while(i-->0) cnt[i]+=sum,tot+=sum/10*level,sumr+=sum;
	}
	for(i=0;i<=9;i++) cnt[i]-=sum/10; tot-=sum/10*(level-1);
	for(i=0;i<9;i++) printf("%llu ",tot+cnt[i]);
	printf("%llu\n",tot+cnt[i]);
}

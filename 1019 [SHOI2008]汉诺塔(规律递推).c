char opt[6][4];
short plate[3][31],*top[3],last,o,n,x,cnt[4],a,b;
long long Ans;
#define sum(i) (top[i]-plate[i])
int main(){
	scanf("%u",&n);
	for(o=0;o<6;o++){
		scanf("%s",opt[o]);
		opt[o][0]-='A';
		opt[o][1]-='A';
	}
	*plate[0]=*plate[1]=*plate[2]=n;
	for(x=2;x<=3;x++){
		for(top[0]=plate[0];sum(0)<=x;*top[0]=n-sum(0)+1) *top[0]++;
		top[1]=plate[1];
		top[2]=plate[2];
		last=3;
		cnt[x]=0;
		do
			for(o=0;o<6;o++) if(opt[o][0]!=last&&*top[opt[o][0]]<*top[opt[o][1]]){
				*++top[last=opt[o][1]]=*top[opt[o][0]]--;
				cnt[x]++;
				break;
			}
		while(o<6);
	}
	a=(cnt[3]-cnt[2])/(cnt[2]-1);
	b=cnt[2]-a;
	Ans=1;
	while(--n) Ans=Ans*a+b;
	printf("%llu\n",Ans);
}

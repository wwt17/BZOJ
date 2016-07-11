int n,k,i,j,t; long long l,fr[20]; _Bool f[20];
int main(){
	scanf("%u%u",&n,&k);
	for(fr[0]=1,i=1;i<n;i++) fr[i]=fr[i-1]*i;
	while(k--)
		if(getchar(),getchar()=='P'){
			scanf("%llu",&l); l--;
			for(i=0;i<n;i++) f[i]=0;
			for(i=n-1;i>=0;i--){
				t=l/fr[i];
				l-=t*fr[i];
				for(j=0;f[j]||t--;j++);
				f[j]=1;
				printf("%u%c",j+1,i?' ':'\n');
			}
		}
		else{
			l=0;
			for(i=0;i<n;i++) f[i]=0;
			for(i=n-1;i>=0;i--){
				scanf("%u",&j);
				f[--j]=1;
				for(t=0;j>=0;j--) if(!f[j]) t++;
				l+=t*fr[i];
			}
			printf("%llu\n",l+1);
		}
}

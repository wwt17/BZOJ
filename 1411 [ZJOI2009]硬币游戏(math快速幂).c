_Bool mem[2][100000],*a=mem[0],*b=mem[1],*tmp;
int main(){
	int n,i,j; long long t;
	scanf("%d%I64d",&n,&t);
	for(i=0;i<n;i++){
		static int x; scanf("%d",&x);
		a[i]=x==2;
	}
	_Bool f=t&1; int d=(t>>1)%n,s;
	for(s=1;t;t>>=1,s<<=1,s%=n)
		if(t&1){
			for(i=0,j=s;i<n;i++,++j==n?j=0:0)
				b[i]=a[i]^a[j];
			tmp=a,a=b,b=tmp;
		}
	for(i=0,j=n-d;i<n;i++,++j==n?j=0:0)
		printf(f?"0 %c%c":"%c 0%c",'1'+a[j],i<n-1?' ':'\n');
}

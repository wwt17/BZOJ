#include <cstdio>
const int N=64,P=997,Power=5001;
int n,ans,frac[N],gcd[N][N],inv[P],power[Power];
void init(){
	frac[0]=1;
	for(int i=1;i<=n;i++) frac[i]=frac[i-1]*i%P;
	for(int b=0;b<=n;b++)
		for(int a=0;a<=n;a++)
			gcd[a][b]=b?gcd[b][a%b]:a;
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=(P-P/i)*inv[P%i]%P;
	power[0]=1;
	for(int i=1;i<Power;i++) power[i]=(power[i-1]<<1)%P;
}
struct data{
	int len;
	void search(int,int,int,int,int);
} s[N];
void data::search(int left,int bound,int cnt,int sum,int val){
	if(!left){
		ans=(ans+sum*power[val])%P;
		//printf("2^val/sum = 2^%d/%d\n",val,inv[sum]);
		return;
	}
	for(len=1;len<=left;len++){
		int dsum=sum*inv[len]%P,dval=(val+(len>>1))%P;
		for(data *i=s;i<this;i++) dval=(dval+gcd[len][i->len])%P;
		if(len==bound){
			dsum=dsum*inv[cnt+1]%P;
			this[1].search(left-len,len,cnt+1,dsum,dval);
			break;
		}
		this[1].search(left-len,len,1,dsum,dval);
	}
}
int main(){
	scanf("%d",&n);
	init();
	s->search(n,n+1,1,1,0);
	printf("%d\n",ans);
	scanf("\n");
}

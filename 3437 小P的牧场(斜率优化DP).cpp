/*
f[i]=min{f[j]+sigma(h){(i-h)*b[h]}}+a[i]
sum1[i]=sigma(j){b[j]}
sum2[i]=sigma(j){j*b[j]}
f[i]=min{f[j]+sum2[j]-i*sum1[j]}+i*sum1[i-1]-sum2[i-1]+a[i]

(f[j]+sum2[j])-(f[k]+sum2[k])<i*(sum1[j]-sum1[k])
*/
#include <cstdio>
const int N=1000005;
int n,a[N],b[N],q[N],*head=q,*tail=q;
long long sum1[N],sum2[N],f[N];
inline double calc(const int j,const int k){
	return ((f[j]+sum2[j])-(f[k]+sum2[k]))/(sum1[j]-sum1[k]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	*tail++=0;
	for(int i=1;i<=n;i++){
		while(tail-head>1&&calc(head[1],head[0])<i) head++;
		f[i]=f[*head]+sum2[*head]-i*sum1[*head]+i*sum1[i-1]-sum2[i-1]+a[i];
		sum1[i]=sum1[i-1]+b[i];
		sum2[i]=sum2[i-1]+(long long)i*b[i];
		while(tail-head>1&&calc(tail[-2],tail[-1])>calc(tail[-1],i)) tail--;
		*tail++=i;
	}
	printf("%lld\n",f[n]);
}


/*
Si+={Cj+1}(1<=j<=i)
L++
f[i]=min{ f[j]+(Si-Sj-L)^2 }
X=Si-L
f[i]=min{ f[j]+(X-Sj)^2 }
    =min{ f[j]-2*X*Sj+Sj^2 }+X^2
K=-2*Sj
B=f[j]+Sj^2
C=X^2
f[i]=min{ Kx+B }+C
k1x+b1>k2x+b2
(k1-k2)X>b2-b1
X>(b2-b1)/(k1-k2)
*/
#include <cstdio>
#define long long long
inline long sqr(const long x){return x*x;}
int N,L,i,Ci;
long X;
struct data{
	long S,f;
	long K(){ return -(S<<1); }
	long B(){ return f+sqr(S); }
} q[50001],*head=q,*tail=q,current;
inline double calc(data *line1,data *line2){
	return (double)(line2->B()-line1->B())/(line1->K()-line2->K());
}
int main(){
	scanf("%u%u",&N,&L); L++;
	for(i=1;i<=N;++i){
		scanf("%u",&Ci); X=(current.S+=Ci+1)-L;
		while(head<tail&&X>=calc(head,head+1))
			head++;
		current.f=head->f+sqr(current.S-head->S-L);
		while(head<tail&&calc(tail-1,tail)>calc(tail,&current))
			tail--;
		*++tail=current;
		//printf("%3I64d %3I64d\n",current.S,current.f);
	}
	printf("%I64d\n",current.f);
	//scanf("%u");
}

/*
f[i]=min{ f[j]+ sigma{ Pk*(Xi-Xk) }(j<k<i) }(0<=j<i) +Ci
    =min{ f[j]+ sigma{ Pk*Xi-Pk*Xk } } +Ci
assume sp[i]=prefix_sum(Pi), sm[i]=prefix_sum(Pi*Xi)
f[i]=min{ f[j] +(sp[i]-sp[j])*Xi -(sm[i]-sm[j]) } +Ci
    =min{ -sp[j]*Xi+f[j]+sm[j] } +sp[i]*Xi-sm[i]+Ci
K=-sp[j]
X=Xi
B=f[j]+sm[j]
C=sp[i]*Xi-sm[i]+Ci
f[i]=min{KX+B}+C
K1X+B1 > K2X+B2
(K1-K2)X > B2-B1
X > (B2-B1)/(K1-K2)
*/
#include <cstdio>
#define long long long
int N,L,i,X,Pi,Ci;
struct data{
	long f,sp,sm;
	long K()const{ return -sp; }
	long B()const{ return f+sm; }
} q[1000001],*head=q,*tail=q,current;
inline double calc(data *line1,data *line2){
	return (double)(line2->B()-line1->B())/(line1->K()-line2->K());
}
int main(){
	scanf("%u",&N);
	for(i=1;i<=N;++i){
		scanf("%d%d%d",&X,&Pi,&Ci); current.sp+=Pi; current.sm+=(long)Pi*X;
		while(head<tail&&X>=calc(head,head+1)) head++;
		current.f=head->f+(current.sp-head->sp)*X-(current.sm-head->sm)+Ci;
		while(head<tail&&calc(tail-1,tail)>calc(tail,&current)) tail--;
		*++tail=current;
	}
	printf("%lld\n",current.f);
}

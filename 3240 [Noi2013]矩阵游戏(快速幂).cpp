#include <cstdio>
#define ll long long
const ll P=1000000007;
char n[1000001],m[1000001],*e,*E;
struct data{
	ll a,b;
	data():a(1),b(0){}
	data(ll _a,ll _b):a(_a),b(_b){}
	void operator*=(const data y){
		a=a*y.a%P,b=(b*y.a+y.b)%P;
	}
} ab,cd,tmp;
void power(data &x,char* n){
	data y;
	for(e=n;*e;e++); e--;
	for(E=e;*E=='0';*E--='9');
	(*E)--;
	for(;e>=n;e--){
		*e&=~'0';
		for(data f=x;*e;*e>>=1,f*=f)
			if(*e&1) y*=f;
		/*
		for(char i='0';i<*e;i++)
			y*=x;
		data xx;
		for(char i='0';i<='9';i++)
			xx*=x;
		*/
		data xx=x;
		xx*=x;
		xx*=xx;
		xx*=x;
		xx*=xx;
		x=xx;
	}
	x=y;
}
int main(){
	scanf("%s%s%u%u%u%u",n,m,&ab.a,&ab.b,&cd.a,&cd.b);
	power(ab,m);
	tmp=ab;
	ab*=cd;
	power(ab,n);
	ab*=tmp;
	printf("%u\n",(ab.a+ab.b)%P);
}

#include <cstdio>
const int P=10007;
int main(){
	int n=0,m=3;
	char c;
	while((c=getchar())>='0'&&c<='9')
		n=(n*10+(c-'0'))%P;
	printf("%d\n",(long long)n*(n+1)*(n+2)/6%P);
}

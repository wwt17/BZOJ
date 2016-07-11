#include <cstdio>
int c[4],tot,i,j,S;
long long f[100001];
#define F(x) (x>=0?f[x]:0)
struct query{
	int d[4],s;
	inline void read(){
		scanf("%u%u%u%u%u",&d[0],&d[1],&d[2],&d[3],&s);
	}
	inline long long ans(){
		int u[4]={c[0]*(d[0]+1),c[1]*(d[1]+1),c[2]*(d[2]+1),c[3]*(d[3]+1)};
		return
			 f[s]
			 
			-F(s-u[0])-F(s-u[1])-F(s-u[2])-F(s-u[3])
			
			+F(s-u[0]-u[1])+F(s-u[0]-u[2])+F(s-u[0]-u[3])
			+F(s-u[1]-u[2])+F(s-u[1]-u[3])+F(s-u[2]-u[3])
			
			-F(s-u[0]-u[1]-u[2])-F(s-u[0]-u[1]-u[3])
			-F(s-u[0]-u[2]-u[3])-F(s-u[1]-u[2]-u[3])
			
			+F(s-u[0]-u[1]-u[2]-u[3]);
	}
} a[1000];
int main(){
	scanf("%u%u%u%u%u",&c[0],&c[1],&c[2],&c[3],&tot);
	for(i=0;i<tot;i++){
		a[i].read();
		if(S<a[i].s) S=a[i].s;
	}
	f[0]=1;
	for(j=0;j<4;j++)
		for(i=c[j];i<=S;i++) f[i]+=f[i-c[j]];
	for(i=0;i<tot;i++)
		printf("%llu\n",a[i].ans());
}

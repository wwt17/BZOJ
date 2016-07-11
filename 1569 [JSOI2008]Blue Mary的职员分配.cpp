#include <cstdio>
#include <queue>
#define char short
#define maxn 50
char n,x,y,z,A,B;
bool done[50][maxn][maxn][4];
struct data{
	short day; char n,a,b,dayleft;
};
int main(){
	scanf("%u%u%u%u%u%u",&n,&x,&y,&z,&A,&B);
	std::queue<data> q;
	data now,next;
	#define confine(day,n,a,b,dayleft)\
	if(a<maxn&&b<maxn&&!done[n][a][b][dayleft]) {\
		next=(data){day,n,a,b,dayleft};\
		if(a>=A&&b>=B) goto end;\
		else{ q.push(next); done[n][a][b][dayleft]=true; }\
	}
	#define confine2(day,n,a,b,dayleft)\
		for(int i=0;i<=n;++i)\
			confine(day,n,a+i*x,b+(n-i)*y,dayleft);
	#define confine3(day,n,a,b,dayleft)\
		for(int i=0;i<=n;++i)\
			confine(day,n+1,a+i*x,b+(n-i)*y,dayleft);
	confine(0,n,0,0,3);
	while(!q.empty()){
		now=q.front(); q.pop();
		switch(now.dayleft){
			case 1:
				confine3(now.day+1,now.n,now.a,now.b,3);
				break;
			case 2:
				confine2(now.day+1,now.n,now.a,now.b,1);
				break;
			case 3:
				confine2(now.day+1,now.n,now.a,now.b,3);
				if(now.a<z) break;
				confine2(now.day+1,now.n,now.a-z,now.b,2);
				break;
		}
	}
	end:
	printf("%u\n",next.day);
}

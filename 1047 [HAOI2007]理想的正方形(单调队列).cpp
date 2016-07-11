#include <cstdio>
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
int a,b,n,i,j,Ans=0x7FFFFFFF,mat[1000][1000],
dmax[1000][1000],dmin[1000][1000],
qmax[1000],*maxh,*maxt,
qmin[1000],*minh,*mint;
#define reset() maxh=qmax,maxt=qmax-1,minh=qmin,mint=qmin-1
#define push(x,y) {\
	while(maxh<=maxt&&x>*maxt) maxt--; *++maxt=x;\
	while(minh<=mint&&y<*mint) mint--; *++mint=y;\
}
#define pop(x,y) {\
	if(x==*maxh) maxh++;\
	if(y==*minh) minh++;\
}
int main(){
	read(a),read(b),read(n); n--;
	for(i=0;i<a;i++)
		for(j=0;j<b;j++)
			read(mat[i][j]);
	for(j=0;j<b;j++){
		reset();
		for(i=0;i<n;i++) push(mat[i][j],mat[i][j]);
		for(;i<a;i++){
			push(mat[i][j],mat[i][j]);
			dmax[i][j]=*maxh;
			dmin[i][j]=*minh;
			pop(mat[i-n][j],mat[i-n][j]);
		}
	}
	for(i=n;i<a;i++){
		reset();
		for(j=0;j<n;j++) push(dmax[i][j],dmin[i][j]);
		for(;j<b;j++){
			push(dmax[i][j],dmin[i][j]);
			if(Ans>*maxh-*minh) Ans=*maxh-*minh;
			pop(dmax[i][j-n],dmin[i][j-n]);
		}
	}
	printf("%u\n",Ans);
}

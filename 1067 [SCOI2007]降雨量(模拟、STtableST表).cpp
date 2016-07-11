#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,i,Y,X,y,x,b,year[50001];
char lg[50001];
struct STdata{
	int Max; bool c;
	friend STdata operator+(const STdata a,const STdata b){
		return (STdata){max(a.Max,b.Max),a.c||b.c};
	}
} ST[16][50000],tmp;
inline STdata query(){
	if(x-1-y<=0) return (STdata){0,false};
	int level=lg[x-1-y];
	return ST[level][y+1]+ST[level][x-(1<<level)];
}
int main(){
	scanf("%u",&n);
	for(i=0;i<n;i++) scanf("%d%d",year+i,ST[0]+i);
	for(i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(b=1;n>>b;b++)
		for(i=0;i+(1<<b)<=n;i++)
			(ST[b][i]=ST[b-1][i]+ST[b-1][i+(1<<(b-1))]).c|=
			year[i+(1<<(b-1))-1]+1!=year[i+(1<<(b-1))];
	scanf("%u",&m);
	while(m--){
		scanf("%d%d",&Y,&X);
		y=lower_bound(year,year+n,Y)-year;
		x=lower_bound(year,year+n,X)-year;
		if(year[y]==Y)
			if(year[x]==X)
				if(ST[0][y].Max>=ST[0][x].Max){
					tmp=query();
					if(tmp.Max>=ST[0][x].Max) puts("false");
					else puts(tmp.c||y<x&&(year[y]+1!=year[y+1]||year[x-1]+1!=year[x])?"maybe":"true");
				}
				else puts("false");
			else puts(query().Max>=ST[0][y].Max?"false":"maybe");
		else{
			y--;
			if(year[x]==X) puts(query().Max>=ST[0][x].Max?"false":"maybe");
			else puts("maybe");
		}
	}
}

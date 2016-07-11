#include <cstdio>
#include <queue>
using namespace std;
typedef unsigned short data;
const data mov[24]={
	0x0011,0x0022,0x0044,0x0088,
	0x0110,0x0220,0x0440,0x0880,
	0x1100,0x2200,0x4400,0x8800,
	0x0003,0x0030,0x0300,0x3000,
	0x0006,0x0060,0x0600,0x6000,
	0x000C,0x00C0,0x0C00,0xC000
};
queue<data> q; data s,t,u,v,step[65536],sum1[65536];
void read(data &x){
	x=0;
	for(int i=0;i<4;getchar(),i++)
		for(int j=0;j<4;j++)
			x=x<<1|(getchar()&1);
}
int main(){
	for(int i=0;i<65536;i++) sum1[i]=sum1[i>>1]+(i&1);
	read(s);
	step[s]=1;
	getchar();
	q.push(s);
	read(t);
	while(!q.empty()){
		u=q.front(); q.pop();
		for(char o=0;o<24;o++)
			if(!step[v=u^mov[o]]&&sum1[v]==sum1[u]){
				step[v]=step[u]+1;
				if(v==t) goto end;
				q.push(v);
			}
	}
	end:
	printf("%hu\n",step[t]-1);
}

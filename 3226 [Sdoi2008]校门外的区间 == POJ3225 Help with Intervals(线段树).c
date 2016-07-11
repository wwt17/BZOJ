#include <stdio.h>
#define bool _Bool
#define false 0
#define true 1
struct data{
	bool cov,xot,mes;
} t[262144];
#define MAX 131070
#define Base 131072
#define down(i) {\
	if(!t[i].mes)\
		t[i<<1].cov=t[i<<1|1].cov=t[i].cov,\
		t[i<<1].mes=t[i<<1|1].mes=0;\
	if(t[i].xot&&t[i].mes)\
		t[i<<1].xot^=1,t[i<<1|1].xot^=1,\
		t[i<<1].cov^=1,t[i<<1|1].cov^=1,\
		t[i].xot=0;\
}
inline void update(const int i){
	if(! (t[i].mes= t[i<<1].mes || t[i<<1|1].mes || t[i<<1].cov^t[i<<1|1].cov) )
		t[i].cov=t[i<<1].cov;
	t[i].xot=false;
}
void correct(int i){
	if(i>>=1){ correct(i); down(i); }
}
inline void cover(int l,int r,const bool c){
	if(l>r) return;
	for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;update(l>>=1),update(r>>=1)){
		if(!(l&1)) t[l^1].cov=c,t[l^1].mes=false;
		if(  r&1 ) t[r^1].cov=c,t[r^1].mes=false;
	}
	while(l>>=1) update(l);
}
inline void xoter(int l,int r){
	if(l>r) return;
	for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;update(l>>=1),update(r>>=1)){
		if(!(l&1)) t[l^1].xot^=1,t[l^1].cov^=1;
		if(  r&1 ) t[r^1].xot^=1,t[r^1].cov^=1;
	}
	while(l>>=1) update(l);
}
bool empty=true;
void Free(int i){
	static int l=0,r=0; static int len=Base<<1;
	len>>=1;
	if(i<Base&&t[i].mes){
		down(i);
		Free(i<<1);
		Free(i<<1|1);
	}
	else
		if(t[i].cov) r+=len; else{
			if(r-l) empty?empty=false:putchar(' '),printf("%c%u,%u%c",l&1?'(':'[',l>>1,r>>1,r&1?']':')');
			l=r+=len;
		}
	len<<=1;
}
int main(){
	char opt,left,right; int l,r;
	while(scanf("%c %c%u,%u%c\n",&opt,&left,&l,&r,&right)!=EOF)
		switch(l=(l<<1)+(left=='('),r=(r<<1)-(right==')'),opt){
			case 'U': cover(l,r,1); break;
			case 'I': cover(0,l-1,0); cover(r+1,MAX,0); break;
			case 'D': cover(l,r,0); break;
			case 'C': cover(0,l-1,0); cover(r+1,MAX,0);
			case 'S': xoter(l,r);
		}
	Free(1);
	empty?printf("empty set"):0;
}


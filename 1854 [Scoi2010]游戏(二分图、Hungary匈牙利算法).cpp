#include <cstdio>
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
struct node;
struct edge{
	node** ed; edge* next;
} E[2000000],*newE=E;
struct node{
	edge* son; bool used;
	bool extend();
} c[10001],*pre[1000000];
int N,Ans;
bool node::extend(){
	if(!this) return true;
	if(used) return false;
	used=true;
	for(edge* e=son;e;e=e->next)
		if((*e->ed)->extend())
			return *e->ed=this,true;
	return false;
}
int main(){
	read(N);
	for(int i=0,a;i<N;i++){
		read(a); *newE=(edge){pre+i,c[a].son}; c[a].son=newE++;
		read(a); *newE=(edge){pre+i,c[a].son}; c[a].son=newE++;
	}
	for(Ans=1;Ans<=10000;Ans++){
		for(int i=1;i<=10000;i++) c[i].used=false;
		if(!c[Ans].extend()) break;
	}
	printf("%u\n",--Ans);
}

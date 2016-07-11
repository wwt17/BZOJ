#include <cstdio>
#include <algorithm>
#include <vector>
const int N=300001,Q=300000,inf=(100+Q)*1000;
inline int getint(){
	int c; bool ne=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') ne=true;
	int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return ne?-a:a;
}
inline void println(int a){
	if(!a){ putchar('0'); putchar('\n'); return; }
	if(a<0) putchar('-'),a=-a;
	static char s[10],*top=s;
	while(a) *top++='0'+a%10,a/=10;
	while(top>s) putchar(*--top);
	putchar('\n');
}
int n,q,base;
struct seg{
	int delta,max;
} t[1<<20];
#define update(x) t[x].max=std::max(t[x<<1].max,t[x<<1|1].max)+t[x].delta
void modify(int l,int r,int d){
	for(l--,r++;l^r^1;l>>=1,update(l),r>>=1,update(r)){
		if(!(l&1)) t[l^1].delta+=d,t[l^1].max+=d;
		if(  r&1 ) t[r^1].delta+=d,t[r^1].max+=d;
	}
	while(l>>=1) update(l);
}
int ask(int l,int r){
	int lmax=-inf,rmax=-inf;
	for(l--,r++;l^r^1;lmax+=t[l>>=1].delta,rmax+=t[r>>=1].delta){
		if(!(l&1)) lmax=std::max(lmax,t[l^1].max);
		if(  r&1 ) rmax=std::max(rmax,t[r^1].max);
	}
	lmax=std::max(lmax,rmax);
	while(l>>=1) lmax+=t[l].delta;
	return lmax;
}
struct node{
	node *belong; int a,l,r; std::vector<node*> son;
	node* get(){
		if(belong==this) return this;
		return belong=belong->get();
	}
	void dfs(){
		static int len=base;
		l=r=++len;
		t[l].max=t[l].delta=a;
		for(std::vector<node*>::iterator it=son.begin();it!=son.end();it++)
			(*it)->dfs();
	}
} V[N];
struct query{
	char type[3]; int x,y; node *u,*v;
	void read(){
		scanf("%s",type);
		if(type[0]=='U'){
			x=getint(),y=getint();
			u=V[x].get(),v=V[y].get();
			if(u==v) return;
			v->belong=u;
			u->son.push_back(v);
		}else{
			switch(type[1]){
				case '1':
					x=getint();
					break;
				case '2':
					x=getint();
					u=V[x].get();
			}
			if(type[0]=='A')
				y=getint();
		}
	}
	void work(){
		switch(type[0]){
			case 'U':
				if(u==v) break;
				u->r=v->r;
				break;
			case 'A':
				switch(type[1]){
					case '1':
						modify(V[x].l,V[x].l,y);
						break;
					case '2':
						modify(u->l,u->r,y);
						break;
					case '3':
						modify(base+1,base+n,y);
				}
				break;
			case 'F':
				switch(type[1]){
					case '1':
						println(ask(V[x].l,V[x].l));
						break;
					case '2':
						println(ask(u->l,u->r));
						break;
					case '3':
						println(ask(base+1,base+n));
				}
				break;
		}
	}
} s[Q];
int main(){
	n=getint();
	for(base=1;base<n+2;base<<=1);
	for(int i=1;i<=n;i++){
		V[i].belong=V+i;
		V[i].a=getint();
	}
	q=getint();
	for(int i=0;i<q;i++) s[i].read();
	for(int i=1;i<=n;i++) if(V[i].belong==V+i)
		V[i].dfs();
	for(int l=base>>1,r=(base+n+1)>>1;l^r^1;l>>=1,r>>=1)
		for(int i=l+1;i<r;i++) update(i);
	for(int i=0;i<q;i++) s[i].work();
}

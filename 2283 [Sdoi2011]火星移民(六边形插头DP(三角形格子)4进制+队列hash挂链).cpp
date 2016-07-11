#include <cstdio>
#include <algorithm>
using namespace std;
const int N=6,Size=5000005,P=9999991,mo=(int)1e9+7;
struct data{
	int s,v,c; data *next;
	void work0();
	void work1();
};
int n;

struct arr{
	int len;
	data a[Size],*h[P];
	void add(int s,int v,int c){
		int x=s%P;
		for(data *i=h[x];i;i=i->next) if(i->s==s){
			if(v<i->v) i->v=v,i->c=0;
			if(v==i->v) if((i->c+=c)>=mo) i->c-=mo;
			return;
		}
		a[len].s=s;
		a[len].v=v;
		a[len].c=c;
		a[len].next=h[x];
		h[x]=a+len;
		len++;
	}
	void clear(){
		while(len)
			h[a[--len].s%P]=NULL;
	}
} mem[2],*f=mem,*g=mem+1;

void rev(){
	arr *tmp=f;
	f=g;
	g=tmp;
	g->clear();
}

int z,loc,locx,locy;

void data::work0(){
	int x=s>>2*loc&3;
	int t=s>>2*(loc+1)<<2*(loc+2) | s&((1<<2*loc)-1);
	if(x) v++;
	if(!z){
		if(!x){
			g->add(t,v,c);
			g->add(t | 1<<2*loc | 1<<2*(loc+1),v,c);
			g->add(t | 2<<2*loc | 2<<2*(loc+1),v,c);
			g->add(t | 3<<2*loc | 3<<2*(loc+1),v,c);
		}
		else{
			g->add(t | x<<2*loc,v,c);
			g->add(t | x<<2*(loc+1),v,c);
		}
	}
	else
	if(z==4){
		if(x) return;
		g->add(t,v,c);
	}
	else{
		if(!x){
			g->add(t | z<<2*loc,v,c);
			g->add(t | z<<2*(loc+1),v,c);
		}
		else{
			if(x!=z) return;
			g->add(t,v,c);
		}
	}
}

void data::work1(){
	int x=s>>2*locx&3,y=s>>2*locy&3;
	int t=s>>2*(locy+1)<<2*locy | s&((1<<2*locx)-1);
	if(x) v++;
	if(y) v++;
	if(!z){
		if(!x)
			if(!y){
				g->add(t,v,c);
			}
			else{
				g->add(t|y<<2*locx,v,c);
			}
		else
			if(!y){
				g->add(t|x<<2*locx,v,c);
			}
			else{
				if(x!=y) return;
				g->add(t,v,c);
			}
	}
	else
	if(z==4){
		if(x||y) return;
		g->add(t,v,c);
	}
	else{
		if(!x)
			if(!y){
				g->add(t|z<<2*locx,v,c);
			}
			else{
				if(y!=z) return;
				g->add(t,v,c);
			}
		else
			if(!y){
				if(x!=z) return;
				g->add(t,v,c);
			}
			else
				return;
	}
}

int main(){
while(scanf("%d",&n)!=EOF){
	f->add(0,0,1);
	for(int i=0;i<n;rev(),i++){
		for(int j=0;j<(n+i)*2+1;rev(),j++){
			scanf("%d",&z);
			if((j&1)==0){
				loc=j>>1;
				for(data *cur=f->a;cur<f->a+f->len;cur++)
					cur->work0();
			}
			else{
				locx=(j+1)>>1,locy=locx+1;
				for(data *cur=f->a;cur<f->a+f->len;cur++)
					cur->work1();
			}
		}
		int loc=((n+i)*2+2)>>1;
		for(data *cur=f->a;cur<f->a+f->len;cur++){
			int x=cur->s>>2*loc&3;
			if(x) continue;
			g->add(cur->s<<2,cur->v,cur->c);
		}
	}
	for(int i=n-1;i>=0;rev(),i--){
		for(int j=0;j<(n+i)*2+1;rev(),j++){
			scanf("%d",&z);
			if((j&1)==0){
				locx=j>>1,locy=locx+1;
				for(data *cur=f->a;cur<f->a+f->len;cur++)
					cur->work1();
			}
			else{
				loc=j>>1;
				for(data *cur=f->a;cur<f->a+f->len;cur++)
					cur->work0();
			}
		}
		int loc=((n+i)*2+1)>>1;
		for(data *cur=f->a;cur<f->a+f->len;cur++){
			int x=cur->s>>2*loc&3;
			if(x) continue;
			g->add(cur->s<<2,cur->v,cur->c);
		}
	}
	bool ok=false;
	for(data *i=f->h[0];i;i=i->next) if(i->s==0){
		ok=true;
		printf("%d %d\n",i->v,i->c);
	}
	if(!ok)
		puts("-1 -1");
	f->clear();
}
}

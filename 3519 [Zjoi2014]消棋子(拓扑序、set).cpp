#include <cstdio>
#include <list>
#include <set>
using namespace std;
const int N=(int)1e5+5,M=(int)1e5+5;
const char str[]="UDLR";
int r,c,n,m;

inline int gc(){
	while(true)
		switch(getchar()){
			case 'U': return 0;
			case 'D': return 1;
			case 'L': return 2;
			case 'R': return 3;
		}
}

struct vec{
	int x,y;
	vec(){
	}
	vec(int _x,int _y):x(_x),y(_y){
	}
	bool operator != (const vec &b){
		return x!=b.x||y!=b.y;
	}
} a[N][2];

bool dele[N],done[N];

struct cmpx{
	bool operator () (const vec *a,const vec *b) const{
		return a->x<b->x;
	}
};

struct cmpy{
	bool operator () (const vec *a,const vec *b) const{
		return a->y<b->y;
	}
};

typedef set<vec*,cmpy> setx;
setx sx[M];
setx::iterator ix[N][2];

typedef set<vec*,cmpx> sety;
sety sy[M];
sety::iterator iy[N][2];

void read(int num,int o){
	int x,y; scanf("%d%d",&x,&y);
	a[num][o]=vec(x,y);
	ix[num][o]=sx[x].insert(&a[num][o]).first;
	iy[num][o]=sy[y].insert(&a[num][o]).first;
}

list<int> q;

struct opt{
	vec x;
	int d1,d2;
	void read(){
		scanf("%d%d",&x.x,&x.y);
		d1=gc();
		d2=gc();
	}
	void print(){
		printf("%d %d %c %c\n",x.x,x.y,str[d1],str[d2]);
	}
} ans[N],*tot=ans;

inline bool findvec(vec *cur){
	return
		sx[cur->x].find(cur)!=sx[cur->x].end()
	&&	sy[cur->y].find(cur)!=sy[cur->y].end();
}

inline vec *find(vec *cur,int d){
	switch(d){
		case 0: return *--sy[cur->y].lower_bound(cur);
		case 1: return *  sy[cur->y].upper_bound(cur);
		case 2: return *--sx[cur->x].lower_bound(cur);
		case 3: return *  sx[cur->x].upper_bound(cur);
	}
}

void check(int num);

void del0(int num){
	//printf("del0 %c\n",'@'+num);
	dele[num]=done[num]=true;
	sx[a[num][0].x].erase(ix[num][0]++);
	sx[a[num][1].x].erase(ix[num][1]++);
	sy[a[num][0].y].erase(iy[num][0]++);
	sy[a[num][1].y].erase(iy[num][1]++);
}

void del(int num){
	//printf("del %c\n",'@'+num);
	if(!findvec(a[num]  )||!findvec(a[num]+1)) return;
	dele[num]=done[num]=true;
	sx[a[num][0].x].erase(ix[num][0]++);
	sx[a[num][1].x].erase(ix[num][1]++);
	sy[a[num][0].y].erase(iy[num][0]++);
	sy[a[num][1].y].erase(iy[num][1]++);
	check((*  ix[num][0]-a[0])/2);
	check((*--ix[num][0]-a[0])/2);
	check((*  ix[num][1]-a[0])/2);
	check((*--ix[num][1]-a[0])/2);
	check((*  iy[num][0]-a[0])/2);
	check((*--iy[num][0]-a[0])/2);
	check((*  iy[num][1]-a[0])/2);
	check((*--iy[num][1]-a[0])/2);
}

void print();

void check(int num){
	if(num<1||num>n||done[num]) return;
	//printf("check %c\n",'@'+num);
	setx::iterator
		x0=ix[num][0],
		x1=ix[num][1];
	setx::iterator
		y0=iy[num][0],
		y1=iy[num][1];
	if(a[num][0].x<a[num][1].x){
		if(a[num][0].y<a[num][1].y){
			if((*++x0)->y>a[num][1].y&&(*--y1)->x<a[num][0].x){
				tot->x=vec(a[num][0].x,a[num][1].y);
				tot->d2=1;
				tot->d1=2;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
			if((*++y0)->x>a[num][1].x&&(*--x1)->y<a[num][0].y){
				tot->x=vec(a[num][1].x,a[num][0].y);
				tot->d1=0;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
		else
		if(a[num][0].y>a[num][1].y){
			if((*--x0)->y<a[num][1].y&&(*--y1)->x<a[num][0].x){
				tot->x=vec(a[num][0].x,a[num][1].y);
				tot->d1=1;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
			if((*++y0)->x>a[num][1].x&&(*++x1)->y>a[num][0].y){
				tot->x=vec(a[num][1].x,a[num][0].y);
				tot->d1=0;
				tot->d2=2;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
		else{
			if(++y0==y1){
				tot->x=vec(a[num][0].x+1,a[num][0].y);
				tot->d1=0;
				tot->d2=1;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
	}
	else
	if(a[num][0].x>a[num][1].x){
		if(a[num][0].y<a[num][1].y){
			if((*++x0)->y>a[num][1].y&&(*++y1)->x>a[num][0].x){
				tot->x=vec(a[num][0].x,a[num][1].y);
				tot->d2=0;
				tot->d1=2;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
			if((*--y0)->x<a[num][1].x&&(*--x1)->y<a[num][0].y){
				tot->x=vec(a[num][1].x,a[num][0].y);
				tot->d1=1;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
		else
		if(a[num][0].y>a[num][1].y){
			if((*--x0)->y<a[num][1].y&&(*++y1)->x>a[num][0].x){
				tot->x=vec(a[num][0].x,a[num][1].y);
				tot->d1=0;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
			if((*--y0)->x<a[num][1].x&&(*++x1)->y>a[num][0].y){
				tot->x=vec(a[num][1].x,a[num][0].y);
				tot->d1=1;
				tot->d2=2;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
		else{
			if(--y0==y1){
				tot->x=vec(a[num][0].x-1,a[num][0].y);
				tot->d1=0;
				tot->d2=1;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
	}
	else{
		if(a[num][0].y<a[num][1].y){
			if(++x0==x1){
				tot->x=vec(a[num][0].x,a[num][0].y+1);
				tot->d1=2;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
		else
		if(a[num][0].y>a[num][1].y){
			if(--x0==x1){
				tot->x=vec(a[num][0].x,a[num][0].y-1);
				tot->d1=2;
				tot->d2=3;
				tot++;
				q.push_back(num);
				done[num]=true;
				return;
			}
		}
	}
}

void print(){
	return;
	puts("--------------print()---------------");
	for(int x=1;x<=r;x++){
		for(setx::iterator it=sx[x].begin();it!=sx[x].end();it++){
			printf(" %c",'@'+(*it-a[0])/2);
		}
		puts("");
	}
	puts("");
	for(int y=1;y<=c;y++){
		for(sety::iterator it=sy[y].begin();it!=sy[y].end();it++){
			printf(" %c",'@'+(*it-a[0])/2);
		}
		puts("");
	}
	puts("-----------end print()--------------");
}

int main(){
	scanf("%d%d%d",&r,&c,&n);
	for(int x=1;x<=r;x++){
		sx[x].insert(new vec(x,0));
		sx[x].insert(new vec(x,c+1));
	}
	for(int y=1;y<=c;y++){
		sy[y].insert(new vec(0,y));
		sy[y].insert(new vec(r+1,y));
	}
	for(int i=1;i<=n;i++){
		read(i,0);
		read(i,1);
	}
	scanf("%d",&m);
	while(m--){
		tot->read();
		if(findvec(&tot->x)) continue;
		vec *n1=find(&tot->x,tot->d1),*n2=find(&tot->x,tot->d2);
		int num1=(n1-a[0])/2,num2=(n2-a[0])/2;
		if(*n1!=tot->x&&1<=num1&&num1<=n&&1<=num2&&num2<=n&&num1==num2){
			tot++;
			//opt *tmp=++tot;
			del0(num1);
			//tot=tmp;
		}
		print();
	}
	printf("%d\n",tot-ans);
	/*
	printf("q: ");
	for(list<int>::iterator it=q.begin();it!=q.end();dele[*it]?q.erase(it++):it++)
		printf(" %c",'@'+*it);
	puts("");
	*/
	for(int i=1;i<=n;i++) if(!done[i])
		check(i);
	while(!q.empty()){
	/*
	printf("q: ");
	for(list<int>::iterator it=q.begin();it!=q.end();it++)
		printf(" %c",'@'+*it);
	puts("");
	*/
		del(q.front());
		q.pop_front();
	}
	printf("%d\n",tot-ans);
	for(opt *cur=ans;cur<tot;cur++)
		cur->print();
	scanf("\n");
}

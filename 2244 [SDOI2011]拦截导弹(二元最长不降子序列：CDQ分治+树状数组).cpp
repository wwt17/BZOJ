#include <cstdio>
#include <algorithm>
using namespace std;
const int N=(int)5e4+5,inf=(int)1e9+7;

int n,Y,ord[N];

struct data{
	int v; double c;
	void clear(){
		c=v=0;
	}
	void renew(data b){
		if(b.v>v){
			v=b.v;
			c=0;
		}
		if(b.v==v)
			c+=b.c;
	}
} ans,t[N];

struct vec{
	int x,y;
	data f,g;
} a[N];

bool cmp(const vec *a,const vec *b){
	return a->x<b->x||a->x==b->x&&a->y<b->y;
}

data query(int y){
	data ans;
	ans.clear();
	for(;y;y-=y&-y) ans.renew(t[y]);
	return ans;
}

void modify(int y,data d){
	for(;y<=Y;y+=y&-y) t[y].renew(d);
}

void erase(int y){
	for(;y<=Y;y+=y&-y) t[y].clear();
}

vec *seq[N];

void work1(int beg,int end){
	if(end-beg==1){
		a[end].f.v++;
		return;
	}
	int mid=beg+end>>1;
	work1(beg,mid);
	for(int i=beg+1;i<=end;i++) seq[i]=a+i;
	stable_sort(seq+beg+1,seq+end+1,cmp);
	for(int i=beg+1;i<=end;i++)
		if(seq[i]<=a+mid)
			modify(seq[i]->y,seq[i]->f);
		else
			seq[i]->f.renew(query(seq[i]->y));
	for(int i=beg+1;i<=mid;i++)
		erase(a[i].y);
	work1(mid,end);
}
void work2(int beg,int end){
	if(end-beg==1){
		a[end].g.v++;
		return;
	}
	int mid=beg+end>>1;
	work2(mid,end);
	for(int i=beg+1;i<=end;i++) seq[i]=a+i;
	stable_sort(seq+beg+1,seq+end+1,cmp);
	for(int i=end;i>beg;i--)
		if(seq[i]>a+mid)
			modify(Y+1-seq[i]->y,seq[i]->g);
		else
			seq[i]->g.renew(query(Y+1-seq[i]->y));
	for(int i=mid+1;i<=end;i++)
		erase(Y+1-a[i].y);
	work2(beg,mid);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].x=inf-a[i].x;
		a[i].y=inf-a[i].y;
		ord[i]=a[i].y;
	}
	sort(ord+1,ord+n+1);
	Y=unique(ord+1,ord+n+1)-ord-1;
	for(int i=1;i<=n;i++){
		a[i].y=lower_bound(ord+1,ord+Y+1,a[i].y)-ord;
		a[i].f=a[i].g=(data){0,1};
	}
	work1(0,n);
	work2(0,n);
	for(int i=1;i<=n;i++) ans.renew(a[i].f);
	printf("%d\n",ans.v);
	for(int i=1;i<=n;i++){
		if(a[i].f.v+a[i].g.v-1!=ans.v)
			putchar('0');
		else
			printf("%.12lf",a[i].f.c*a[i].g.c/ans.c);
		putchar(" \n"[i==n]);
	}
}

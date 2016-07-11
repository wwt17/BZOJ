#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Type int
#define kD 2
inline void maxi(Type &a,const Type b){if (a<b) a=b;}
inline void mini(Type &a,const Type b){if (a>b) a=b;}
inline int getint(){
	char c;bool f=false;int a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
	return a;
}
inline void read(int &a){
	char c;bool f=false;a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
}
struct point{
	Type p[kD];
	void read(){
		for (int i=0;i<kD;++i) p[i]=getint();
	}
};
point p,*Base;
struct kd_tree{
	point x,min,max; unsigned split; kd_tree* c[2];
	kd_tree(point &_x,unsigned _split,kd_tree* _l,kd_tree* _r):split(_split){
		memcpy(&x,&_x,sizeof(point));
		memcpy(&max,&x,sizeof(point));
		memcpy(&min,&x,sizeof(point));
		if (c[0]=_l)
			for (int i=0;i<kD;++i)
				maxi(max.p[i],c[0]->max.p[i]),
				mini(min.p[i],c[0]->min.p[i]);
		if (c[1]=_r)
			for (int i=0;i<kD;++i)
				maxi(max.p[i],c[1]->max.p[i]),
				mini(min.p[i],c[1]->min.p[i]);
	}
};
unsigned fd;
inline bool cmp(const point &a,const point &b){
	return a.p[fd]<b.p[fd];
}
const Type ansinf=0x7fffffff;
Type ans;
kd_tree* build(point* begin,point* end){
	if (end-begin<=0) return NULL;
	++fd==kD?fd=0:0; int d=fd;
	point* mid=begin+(end-begin)/2;
	std::nth_element(begin,mid,end,cmp);
	return new kd_tree(*mid,d,build(begin,mid),build(mid+1,end));
}
inline Type mht_dist(point &p,point &q){
	Type ret=0;
	for (int i=0;i<kD;++i) ret+=abs(p.p[i]-q.p[i]);
	return ret;
}
inline Type mht_dist(const point &p,const kd_tree* rec){
	Type ret=0;
	for (int i=0;i<kD;++i)
		if (p.p[i]<rec->min.p[i]) ret+=rec->min.p[i]-p.p[i]; else
		if (p.p[i]>rec->max.p[i]) ret+=p.p[i]-rec->max.p[i];
	return ret;
}
void insert(kd_tree* &This){
	if (!This){ This=new kd_tree(p,++fd==kD?fd=0:0,NULL,NULL);return; }
	fd=This->split;
	insert(This->c[This->x.p[fd]<p.p[fd]]);
	for (int i=0;i<kD;++i)
		maxi(This->max.p[i],p.p[i]),
		mini(This->min.p[i],p.p[i]);
}
void nearest(kd_tree* This){
	if (!This||mht_dist(p,This)>=ans) return;
	mini(ans,mht_dist(p,This->x));
	fd=This->split;
	bool gotoright=This->x.p[fd]<p.p[fd];
	nearest(This->c[gotoright]);
	nearest(This->c[!gotoright]);
}
int main(){
	int N,M; read(N),read(M);
	point b[N]; Base=b;
	for (int i=0;i<N;++i) b[i].read();
	fd=kD-1;
	kd_tree *flat=build(b,b+N);
	int t;
	while (M--){
		read(t),read(p.p[0]),read(p.p[1]);
		if (t==1) fd=kD-1,insert(flat);
		else ans=ansinf,nearest(flat),printf("%d\n",ans);
	}
}

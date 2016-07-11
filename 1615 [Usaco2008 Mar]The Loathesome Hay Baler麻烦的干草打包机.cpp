#include <cstdio>
#define size 1050
#define X_0 0
#define Y_0 0
inline int sqr(const int &x) {
	return x*x;
}
int N,t0,X_t,Y_t,t,i,j;
struct edge {
	int link;
	edge* next;
	edge(int _link,edge* _next):
};
struct whell {
	int x,y,r,speed;
	edge* son;
	inline void read() {
		scanf("%d%d%d",&x,&y,&r);
		if (x==X_0&&y==Y_0) t0=i;
		if (x==X_t&&y==Y_t) t=i;
	}
	inline void connect(const int &b) {
		edge e(
} w[size];
inline bool influence(const int &a,const int &b) {
	return sqr(w[a].x-w[b].x)+sqr(w[a].y-w[b].y)==sqr(w[a].r+w[b].r);
}
int main() {
	scanf("%d%d%d",&N,&X_t,&Y_t);
	for (i=0;i<N;++i) {
		w[i].read();
		for (j=0;j<i;++j)
			if (influence(w[i],w[j])) {
				w[i].connect(j);
				w[j].connect(i);
			}

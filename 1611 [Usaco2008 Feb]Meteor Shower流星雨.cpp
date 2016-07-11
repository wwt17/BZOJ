#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
#define size 305
#define inf 0x7fffffff
const int dir[5][2]={ -1,0, 1,0, 0,-1, 0,1, 0,0 };
struct square {
	int t,f;
	bool inq;
	square() { t=f=inf; }
	inline void init(int T) {
		if (T<t) 
		t=T;
	}
	inline bool legal() {
		return f<t;
	}
} s[size][size];
struct loca {
	int x,y;
};
int ans=inf;
inline bool inmap(const int &x,const int &y) {
	return x>=0&&y>=0;
}
inline bool relaxed(square* a,square* b) {
	if (!b->legal() || a->f <= b->f+1) return false;
	a->f = b->f+1;
	if (a->legal()) {
		if (a->t==inf&&ans>a->f) ans=a->f;
		return true;
	}
	return false;
}
int main() {
	int M,X,Y,T,d;
	scanf("%d",&M);
	while (M--) {
		scanf("%d%d%d",&X,&Y,&T);
		for (d=0;d<=4;++d) if (inmap(X+dir[d][0],Y+dir[d][1]))
			s[X+dir[d][0]][Y+dir[d][1]].init(T);
	}
	queue<loca> q; loca head;
	for (s[0][0].f=0,s[0][0].inq=true,q.push((loca){0,0});!q.empty();s[head.x][head.y].inq=false,q.pop())
		for (head=q.front(),d=0;d<4;++d)
			if (inmap(X=head.x+dir[d][0],Y=head.y+dir[d][1])&&relaxed(&s[X][Y],&s[head.x][head.y]))
				q.push((loca){X,Y});
	if (ans==inf) ans=-1;
	printf("%d\n",ans);
	//system("pause");
}

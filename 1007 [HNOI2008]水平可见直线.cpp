#include <cstdio>
#include <cstring>
#include <algorithm>
#define sizeN 50001
struct line{
	double A,B;
	void read(){ scanf("%lf%lf",&A,&B); }
};
bool cmpK(const line* a,const line* b){
		return a->A<b->A || a->A==b->A && a->B>b->B;
}
struct point{
	double x,y;
};
inline double itscx(line &a,line &b){
	return -(double)(a.B-b.B)/(a.A-b.A);
}
int N;
line l[sizeN],*p[sizeN];
bool see[sizeN];
int main(){
	scanf("%d",&N);
	int i;
	for (i=1;i<=N;++i) l[i].read(),p[i]=&l[i];
	std::sort(p+1,p+1+N,cmpK);
	line *stack[N+1]; int top=1; stack[top]=p[1];
	for (i=2;i<=N;++i) if (p[i]->A!=p[top]->A){
		while (top>1&&itscx(*p[i],*stack[top])<=
		              itscx(*stack[top],*stack[top-1])) --top;
		stack[++top]=p[i];
	}
	while (top) see[stack[top--]-l]=true;
	for (i=1;i<=N;++i) if (see[i]) printf("%d ",i);
}

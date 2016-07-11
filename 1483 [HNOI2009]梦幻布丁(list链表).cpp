#include <cstdio>
struct putting{
	int color; putting *belong,*next;
} a[100001],*head[1000000],tmp;
int n,m,i,j,X,Y,ans;
inline putting* merge(putting* &x,putting* &y){
	putting *res=!y||x<y?x:y,*last=&tmp;
	while(x||y){
		if(last->belong+1==x){
			ans--;
			last->belong=x->belong;
			x=last;
		}
		else
			last->belong->next=x;
		while(x&&(x<y||!y))
			last=x,x=x->belong->next;
		if(last->belong+1==y){
			ans--;
			last->belong=y->belong;
			y=last;
		}
		else
			last->belong->next=y;
		while(y&&(y<x||!x))
			last=y,y=y->belong->next;
	}
	return res;
}
int main(){
	scanf("%u%u",&n,&m);
	for(i=1;i<=n;i++) scanf("%u",a+i);
	for(i=n,ans=0;i;i=j-1,ans++){
		a[i].next=head[a[i].color];
		for(j=i;a[j-1].color==a[j].color;j--);
		a[j].belong=&a[i];
		head[a[i].color]=&a[j];
	}
	tmp.belong=&tmp;
	while(m--)
		if(scanf("\n"),getchar()=='1'){
			scanf("%u%u",&X,&Y);
			if(X!=Y) head[Y]=merge(head[X],head[Y]);
		}
		else printf("%u\n",ans);
}

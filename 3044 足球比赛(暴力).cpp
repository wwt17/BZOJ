#include <cstdio>
int t,x,y; char where[6];
inline bool pwin(int x1,int y1,int x2,int y2){
	return x1+x2>y1+y2||x1+x2==y1+y2&&x2>=y1;
}
int main(){
	scanf("%u",&t);
	while(t--){
		scanf("\nwccy's team played %s game, scored %d goals, and conceded %d goals.",
			where,&x,&y);
		if(*where=='h'){
			for(int ans=0;ans<=30;ans++)
				if(pwin(x,y,ans,0)){
					printf("%d ",ans);
					break;
				}
			for(int ans=30;ans>=0;ans--)
				if(pwin(30,ans,y,x)){
					printf("%d\n",ans);
					break;
				}
		}
		else{
			for(int ans=0;ans<=30;ans++)
				if(pwin(ans,0,x,y)){
					printf("%d ",ans);
					break;
				}
			for(int ans=30;ans>=0;ans--)
				if(pwin(y,x,30,ans)){
					printf("%d\n",ans);
					break;
				}
		}
	}
}

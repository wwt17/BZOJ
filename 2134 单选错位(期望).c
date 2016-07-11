double ans;
int main(){
	int n,i,A,B,C,a,x,y,X,Y;
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&a);
	X=(x=a)%C+1; a=a%C+1;
	for(i=2;i<=n;i++){
		Y=(y=((long long)x*A+B)%100000001)%C+1;
		ans+=1./(X>Y?X:Y);
		x=y; X=Y;
	}
	printf("%.3lf\n",ans+=1./(X>a?X:a));
	scanf("\n");
}

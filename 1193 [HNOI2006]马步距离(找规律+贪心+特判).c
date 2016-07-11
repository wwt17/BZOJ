int f(int x,int k){
	return x/k+(_Bool)(x%k);
}
int max(int a,int b,int c){
	int t=a>b?a:b;
	return t>c?t:c;
}
int main(){
	int xp,yp,x,y;
	scanf("%d%d%d%d",&xp,&yp,&x,&y);
	x-=xp; y-=yp;
	if(x<0) x*=-1;
	if(y<0) y*=-1;
	int step=max(f(x+y,3),f(x,2),f(y,2));
	if((step^x^y)&1) step++;
	if(x+y==1) step=3;
	if(x==2&&y==2) step=4;
	printf("%d\n",step);
}

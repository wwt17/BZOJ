int n;
long double f,t;
int main(){
	scanf("%d",&n);
	while(n--)
		switch(getchar()){
			case 'o':
				f+=t*2+1;
				t+=1;
				break;
			case 'x':
				t=0;
				break;
			case '?':
				f+=t+.5;
				t=.5*(t+1);
				break;
			default:
				n++;
		}
	printf("%.4lf\n",(double)f);
}

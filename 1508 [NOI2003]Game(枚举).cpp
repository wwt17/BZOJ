#include <cstdio>
#include <cctype>
const int p[2]={1,-1};
int n,e,d;
char c,s[1005];
int f[3][10][11],w[1005]; // 0+ 1- 2=
void add(int i,int j){
	f[0][i][++*f[0][i]]=j;
	f[1][j][++*f[1][j]]=i;
}
void slf(int i,int j){
	f[2][i][++*f[2][i]]=j;
	f[2][j][++*f[2][j]]=i;
}
int main(){
	add(0,8);
	slf(0,6);
	slf(0,9);
	add(1,7);
	slf(2,3);
	add(3,9);
	slf(3,5);
	add(5,6);
	add(5,9);
	add(6,8);
	slf(6,9);
	add(9,8);
	while((c=getchar())!='#'){
		s[++n]=c;
		if(c=='=') e=n;
	}
	for(int i=1,j;i<e;){
		int x; sscanf(s+i,"%d",&x);
		d-=x;
		for(j=i+1;j<e&&isdigit(s[j]);j++);
		i=j;
		for(j=i-1;j>0&&isdigit(s[j]);j--) w[j]=j+1==i?-p[x<0]:w[j+1]*10;
	}
	for(int i=e+1,j;i<=n;){
		int x; sscanf(s+i,"%d",&x);
		d+=x;
		for(j=i+1;j<=n&&isdigit(s[j]);j++);
		i=j;
		for(j=i-1;j>0&&isdigit(s[j]);j--) w[j]=j+1==i?p[x<0]:w[j+1]*10;
	}
	for(int i=1;i<=n;i++) if(w[i])
		for(int j=1;j<=n;j++) if(w[j])
			if(i==j){
				int x=s[i]-'0';
				d-=w[i]*x;
				for(int k=1;k<=*f[2][x];k++){
					int y=f[2][x][k];
					d+=w[j]*y;
					if(!d){
						s[j]=y+'0';
						printf("%s#\n",s+1);
						return scanf("\n"),0;
					}
					d-=w[j]*y;
				}
				d+=w[i]*x;
			}
			else{
				int x=s[i]-'0',y=s[j]-'0';
				d-=w[i]*x+w[j]*y;
				for(int kx=1;kx<=*f[1][x];kx++){
					int xx=f[1][x][kx];
					d+=w[i]*xx;
					for(int ky=1;ky<=*f[0][y];ky++){
						int yy=f[0][y][ky];
						d+=w[j]*yy;
						if(!d){
							s[i]=xx+'0';
							s[j]=yy+'0';
							printf("%s#\n",s+1);
							return scanf("\n"),0;
						}
						d-=w[j]*yy;
					}
					d-=w[i]*xx;
				}
				d+=w[i]*x+w[j]*y;
			}
	puts("No");
}

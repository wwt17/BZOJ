const char c[5]="WING";
int i,j,k,n,l,r,mid,I,sum[4];
char opt[4][16][2],s[202],f[202][202];
int main(){
	for(i=0;i<4;i++) scanf("%u",&sum[i]);
	for(i=0;i<4;i++)
		for(j=0;j<sum[i];j++){
			scanf("\n");
			for(k=0;k<2;k++){
				char ch=getchar();
				for(I=0;I<4;I++) if(ch==c[I]){
					opt[i][j][k]=1<<I;
					break;
				}
			}
		}
	scanf("%s",s);
	for(n=0;s[n];n++)
		for(I=0;I<4;I++) if(s[n]==c[I]){
			s[n]=1<<I;
			break;
		}
	for(l=n-1;l>=0;l--){
		f[l][l+1]=s[l];
		for(r=l+2;r<=n;r++)
			for(i=0;i<4;i++){
				for(mid=l+1;mid<r;mid++)
					for(j=0;j<sum[i];j++)
						if(f[l][mid]&opt[i][j][0]
						&& f[mid][r]&opt[i][j][1]){
							f[l][r]|=1<<i;
							goto out;
						}
				out:;
			}
	}
	_Bool wrong=1;
	for(I=0;I<4;I++) if(f[0][n]&(1<<I)) putchar(c[I]),wrong=0;
	if(wrong) printf("The name is wrong!");
	putchar('\n');
}

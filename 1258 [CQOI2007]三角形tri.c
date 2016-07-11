char s[52];
int len;
_Bool f[128];
int main(){
	scanf("%s",s);
	for(;s[len];len++);
	if(s[--len]=='4'){
		for(s[len]='1';s[len]<'4';s[len]++)
			puts(s);
		return 0;
	}
	for(;len;len--)
		if(!f[s[len]]){
			f[s[len]]=1;
			s[len]='4';
			s[len+1]=0;
			puts(s);
		}
	scanf("\n");
}

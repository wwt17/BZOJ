int N,M,m,mm,h,w,len,cnt,l;
char s[101][10500],*t[101];
int main(){
	for(m=0;m<=100;++m) t[m]=s[m];
	scanf("%u",&N);
	while(N--){
		scanf("%u",&M);
		for(;h<M;++h)
			for(l=1;l<=w;++l)
				*t[h+1]++=',';
		scanf("%s",t[0]); while(*++t[0]); *t[0]++=','; len=1;
		for(m=1;m<=M;++m){
			scanf("%s",t[m]);
			for(cnt=1;*t[m];++t[m]) if(*t[m]==',') ++cnt;
			for(;len<cnt;++len)
				for(mm=0;mm<m;++mm)
					*t[mm]++=',';
			for(;cnt<=len;++cnt)
			*t[m]++=',';
		}
		for(;M<h;++M)
			for(l=1;l<=len;++l)
				*t[M+1]++=',';
		w+=len;
	}
	for(m=0;m<=h;++m){
		*--t[m]='\0';
		puts(s[m]);
	}
}

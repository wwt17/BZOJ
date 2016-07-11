int main(){
	int T,N,a,r,f;
	for(scanf("%u",&T);T;T--){
		r=0; f=1;
		for(scanf("%u",&N);N;N--)
			scanf("%u",&a),r^=a,f&=a==1;
		puts(f^r?"John":"Brother");
	}
}

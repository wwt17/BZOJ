const int prime[10]={2,3,5,7,11,13,17,19,23,29};
int N,ans=0x7FFFFFFF;short max;
void DFS(long long now,short cnt,short limit,short k){
	if(cnt==max&&now<ans)
		ans=now;
	if(cnt>max){
		ans=now;
		max=cnt;
	}
	if(k==10) return;
	now*=prime[k];
	short i;
	for(i=1;now<=N&&i<=limit;i++,now*=prime[k])
		DFS(now,cnt*(i+1),i,k+1);
}
int main(){
	scanf("%u",&N);
	DFS(1,1,32,0);
	printf("%u\n",ans);
	scanf("%u");
}

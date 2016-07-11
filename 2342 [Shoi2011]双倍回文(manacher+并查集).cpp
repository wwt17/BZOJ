#include <cstdio>
const int N=500005;
int n,ans;
char s[N*2];
int rad[N*2];
int belong[N*2];
int get(int x){
	return !belong[x]?x:(belong[x]=get(belong[x]));
}

int main(){
	scanf("%d",&n);
	scanf("%s",s);
	s[n*2]='#';
	for(int i=n-1;i>=0;i--){
		s[i*2+1]=s[i];
		s[i*2]='#';
	}
	n=n*2+1;
	for(int i=0,j;i<n;i+=j){
		rad[i]++;
		for(;i-rad[i]>=0&&i+rad[i]<n&&s[i-rad[i]]==s[i+rad[i]];rad[i]++);
		rad[i]--;
		for(j=1;j<=rad[i];j++){
			if(j+rad[i-j]<rad[i])
				rad[i+j]=rad[i-j];
			else
			if(j+rad[i-j]>rad[i])
				rad[i+j]=rad[i]-j;
			else{
				rad[i+j]=rad[i-j];
				break;
			}
		}
		if(s[i]=='#'){
			int k=get(i-rad[i]/2);
			for(;s[k]!='#'||k+rad[k]<i;k=belong[k]=get(k+1));
			if(i-k>ans) ans=i-k;
		}
	}
	printf("%d\n",ans*2);
}
